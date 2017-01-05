#pragma once

#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <memory>

// P430, c++ primer 5th
namespace TextQueryProg {
	namespace NoShare {
		class TextFileLoader {
		public:
			TextFileLoader(std::string const filename) {
				std::ifstream file(filename);
				std::string line;
				for (; std::getline(file, line); line_num_++) {
					std::istringstream sstream(line);
					std::string word;
					while (sstream >> word) {
						word_map_[word].insert(line_num_);
					}
					lines_.emplace_back(line);
				}
			}
			void print(std::string const word)const {
				auto it = word_map_.find(word);
				if (it != word_map_.end()) {
					auto const &set = it->second;
					std::cout << word << " occurs " << set.size() << " times" << std::endl;
					for (auto const &line_num : set) {
						std::cout << "\t(line " << line_num << ") " << lines_[line_num] << std::endl;
					}
				}
			}
		private:
			std::map<std::string, std::set<int>>	word_map_;
			std::vector<std::string>				lines_;
			int										line_num_ = 0;
		};

		void DoTest() {
			std::string filename("C:/Python27/README.txt");
			TextFileLoader loader(filename);
			loader.print(std::string("read"));
		}
	}
	namespace Share {
		class TextLoader {
		public:
			class QueryResult {
				friend class TextLoader;
			public:
				QueryResult() = default;
				void print() {
					std::cout << word_ << " occurs " << total_num_ << " times, in " << line_indices_ptr_->size() << " lines." << std::endl;
					for (auto &idx : *line_indices_ptr_) {
						std::cout << "\t(line " << idx + 1 << ") " << (*text_)[idx] << std::endl;
					}
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
			}
			QueryResult query(std::string const &word)const {
				QueryResult ret;
				auto it = word_map_.find(word);
				if (it != word_map_.end()) {
					auto const &word_info = it->second;
					ret.total_num_	= word_info.total_num;
					ret.text_ = text_;
					ret.word_ = word;
					ret.line_indices_ptr_ = word_info.line_indices_ptr_;
				}
				return ret;
			}
		private:
			std::map<std::string, WordInfo>				word_map_;
			std::shared_ptr<std::vector<std::string>>	text_;
		};

		void DoTest() {
			std::string filename("C:/Python27/README.txt");
			TextLoader *pLoader = new TextLoader(filename);
			auto query_result = pLoader->query("as");
			delete pLoader;
			query_result.print();
		}
	}
	void DoTest() {
		Share::DoTest();
	}
}