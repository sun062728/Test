#pragma once

#include <memory>
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <functional>
#include <cassert>

namespace TestTextQueryProgCh15 {
	namespace MyWay {
		class TextLoader {
		public:
			class QueryResult {
				friend class TextLoader;
			public:
				QueryResult() = default;
				void print() {
					if (line_indices_ptr_) {
						std::cout << word_ << " occurs " << total_num_ << " times, in " << line_indices_ptr_->size() << " lines." << std::endl;
						for (auto &idx : *line_indices_ptr_) {
							std::cout << "\t(line " << idx + 1 << ") " << (*text_)[idx] << std::endl;
						}
					}
					else
						std::cout << word_ << " occurs " << total_num_ << " times, in " << 0 << " lines." << std::endl;
				}
				friend QueryResult operator&(QueryResult const &l, QueryResult const &r) {
					QueryResult ret;

					if (!l.line_indices_ptr_ || !r.line_indices_ptr_)
						return ret;

					auto p = std::make_shared<std::set<int>>();
					for (auto &v : *l.line_indices_ptr_) {
						if ((*r.line_indices_ptr_).find(v) != (*r.line_indices_ptr_).cend())
							(*p).insert(v);
					}
					ret.line_indices_ptr_ = p;
					ret.text_ = l.text_;
					ret.total_num_ = (*p).size();
					ret.word_ = '(' + l.word_ + " & " + r.word_ + ')';
					return ret;
				}
				friend QueryResult operator|(QueryResult const &l, QueryResult const &r) {
					if (!l.line_indices_ptr_)
						return r;
					if (!r.line_indices_ptr_)
						return l;

					auto p = std::make_shared<std::set<int>>();
					for (auto &v : *l.line_indices_ptr_)
						(*p).insert(v);
					for (auto &v : *r.line_indices_ptr_)
						(*p).insert(v);
					QueryResult ret;
					ret.line_indices_ptr_ = p;
					ret.text_ = l.text_;
					ret.total_num_ = (*p).size();
					ret.word_ = '(' + l.word_ + " | " + r.word_ + ')';
					return ret;
				}
			private:
				std::string									word_;
				std::shared_ptr<std::set<int>>				line_indices_ptr_;
				std::shared_ptr<std::vector<std::string>>	text_;
				int											total_num_;

			};

			struct WordInfo {
				std::shared_ptr<std::set<int>>	line_indices_ptr_ = std::make_shared<std::set<int>>();
				int								total_num = 0;
			};

			TextLoader(std::string const filename)
				:text_(std::make_shared<std::vector<std::string>>()) {
				std::ifstream file(filename);
				std::string line;
				int line_num = 0;
				for (; std::getline(file, line); line_num++) {
					std::istringstream sstream(line);
					std::string word;
					while (sstream >> word) {
						word_map_[word].total_num++;
						//if (nullptr == word_map_[word].line_indices_ptr_) {
						//	word_map_[word].line_indices_ptr_ = std::make_shared<std::set<int>>();
						//}
						word_map_[word].line_indices_ptr_->insert(line_num);
					}
					text_->push_back(line);
				}
				// full indices is for '~' use
				for (int i = 0; i < line_num; i++) {
					full_indices_.insert(i);
				}
			}
			QueryResult query(std::string const &word) {
				std::string operand1, operand2;
				QueryResult op1_res, op2_res, ret;
				bool is_op1_rv(false), is_op2_rv(false);
				char op = 0;
				auto word_end = word.cend();

				if (word.empty())
					return QueryResult();

				// get operand1
				auto op1_end = get_operand(word.cbegin(), word, operand1, is_op1_rv);

				// get op
				auto op_it = skip_space(op1_end, word_end);
				if (op_it == word_end) {
					// only 1 operand
					if (is_word(operand1))
						// single word, do basic query and return
						op1_res = do_basic_query(operand1);
					else
						// expression, pass down
						op1_res = query(operand1);
					if (is_op1_rv)
						do_reverse_query(op1_res);
					return op1_res;
				}
				op = *op_it;

				// get operand2
				auto op2_end = get_operand(op_it + 1, word, operand2, is_op2_rv);

				// query
				op1_res = query(operand1);
				op2_res = query(operand2);

				// do op
				// simple factory pattern is preferred
				switch (op) {
				case '&':
					if (is_op1_rv) do_reverse_query(op1_res);
					if (is_op2_rv) do_reverse_query(op2_res);
					ret = op1_res & op2_res;
					break;
				case '|':
					if (is_op1_rv) do_reverse_query(op1_res);
					if (is_op2_rv) do_reverse_query(op2_res);
					ret = op1_res | op2_res;
					break;
				default:
					assert(0);
					break;
				}

				return ret;
			}
		private:
			std::map<std::string, WordInfo>				word_map_;
			std::shared_ptr<std::vector<std::string>>	text_;
			std::set<int>								full_indices_;

			// utils
			bool is_ch(char c) {
				if ((c >= 'a'&& c <= 'z') ||
					(c >= 'A'&& c <= 'Z'))
					return true;
				else
					return false;
			}
			std::string::const_iterator next_not_ch(std::string::const_iterator it, std::string::const_iterator end) {
				while (it != end) {
					if (is_ch(*it))
						it++;
					else
						return it;
				}
				return it;
			}
			bool is_space(char c) {
				if (c == ' ' || c == '\t' || c == '\r')
					return true;
				else
					return false;
			}
			std::string::const_iterator skip_space(std::string::const_iterator it, std::string::const_iterator end) {
				for (; (it != end) && (is_space(*it)); it++) {}
				return it;
			}
			std::string::const_iterator handle_parenthesis(std::string::const_iterator beg, std::string const &word, std::string &o) {
				std::string::const_reverse_iterator r_it;
				for (r_it = word.crbegin(); (r_it != word.crend()) && (*r_it != ')'); r_it++) {}
				if (r_it == word.crend())
					assert(0);
				auto end = r_it.base();
				o.assign(beg + 1, end - 1);
				return end;
			}
			bool has_op(std::string const s) {
				if ((s.find('&') == std::string::npos) ||
					(s.find('|') == std::string::npos) ||
					(s.find('&') == std::string::npos))
					return true;
				else
					return false;
			}
			bool has_parenthesis(std::string const s) {
				if ((s.find('(') == std::string::npos) ||
					(s.find(')') == std::string::npos))
					return true;
				else
					return false;
			}
			bool is_word(std::string const s) {
				for (auto &c : s) {
					if (!is_ch(c))
						return false;
				}
				return true;
			}
			std::string::const_iterator get_operand(std::string::const_iterator beg, std::string const &word, std::string &o, bool &bReverse) {
				size_t offset = 0;
				decltype(beg) end;
				auto word_end = word.cend();
				beg = skip_space(beg, word_end);
				if (*beg == '(') {
					end = handle_parenthesis(beg, word, o);
				}
				else if (is_ch(*beg)) {
					end = next_not_ch(beg, word_end);
					o.assign(beg, end);
				}
				else if (*beg == '~') {
					bReverse = true;
					if (*(++beg) != '(')
						assert(0);
					end = handle_parenthesis(beg, word, o);
				}
				else
					assert(0);
				return end;
			}
			void do_reverse_query(QueryResult &r) {
				r.word_ = "~(" + r.word_ + ')';
				if (!r.line_indices_ptr_)
					return;
				auto p = std::make_shared<std::set<int>>(full_indices_);
				for (auto v : *r.line_indices_ptr_) {
					(*p).erase(v);
				}
				r.line_indices_ptr_ = p;
				r.total_num_ = (*p).size();
			}
			QueryResult do_basic_query(std::string const &s) {
				QueryResult ret;
				auto it = word_map_.find(s);
				if (it != word_map_.end()) {
					ret.line_indices_ptr_ = (*it).second.line_indices_ptr_;
					ret.text_ = text_;
					ret.total_num_ = (*it).second.total_num;
				}
				ret.word_ = s;
				return ret;
			}
		};

		void DoTest() {
			std::string filename("ch15_text.txt");
			TextLoader *pLoader = new TextLoader(filename);
			auto query_result = pLoader->query("((fiery & bird) | wind)");
			delete pLoader;
			query_result.print();
		}
	}

	void DoTest() {
		MyWay::DoTest();
	}
}