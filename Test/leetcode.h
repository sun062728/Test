#pragma once

#include <vector>
#include <algorithm>

namespace TestLeetCode {
	class Solution {
	public:
		std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
			// eliminate duplicate
			std::sort(nums.begin(), nums.end());
			//const auto it_dup = std::unique(nums.begin(), nums.end());
			//nums.erase(it_dup, nums.end());

			std::vector<std::vector<int>> result;
			result.reserve(1000);
			for (auto i = nums.cbegin(); i != nums.cend(); ++i) {
				for (auto j = i + 1; j != nums.cend(); ++j) {
					for (auto k = j + 1; k != nums.cend(); ++k) {
						if (*i + *j + *k == 0) {
							std::vector<int> res;
							res.push_back(*i);
							res.push_back(*j);
							res.push_back(*k);
							result.push_back(res);
						}
					}
				}
			}

			std::sort(result.begin(), result.end());
			const auto it_dup = std::unique(result.begin(), result.end());
			result.erase(it_dup, result.end());
			return result;
		}
	};

	void DoTest() {
		std::vector<int> nums{7,-10,7,3,14,3,-2,-15,7,-1,-7,6,-5,-1,3,-13,6,-15,-10,14,8,5,-10,-1,1,1,11,
			6,8,5,-4,0,3,10,-12,-6,-2,-6,-6,-10,8,-5,12,10,1,-8,4,-8,-8,2,-9,-15,14,-11,-1,-8,5,-13,14,-2,0,
			-13,14,-12,12,-13,-3,-13,-12,-2,-15,4,8,4,-1,-6,11,11,-7,-12,-2,-8,10,-3,-4,-6,4,-14,-12,-5,0,3,
			-3,-9,-2,-6,-15,2,-11,-11,8,-11,8,-7,8,14,-5,4,10,3,-1,-15,10,-6,-11,13,-5,1,-15};

		Solution s;
		auto vv = s.threeSum(nums);

		/*std::sort(nums.begin(), nums.end());
		std::*/

	}
}