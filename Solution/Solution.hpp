//
// Created by yangc on 24-12-9.
//

# pragma once

#include <iostream>
#include "../Stack&Queue/ycLinkedStack.hpp"
#include "../List/SingleList.hpp"
#include "../List/Vector.hpp"
#include <string>

class Solution {
public:
    double findMedianSortedArrays(Vector<int>& nums1, Vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1); // 保证 nums1 是较短数组
        }

        int m = nums1.size();
        int n = nums2.size();
        int imin = 0, imax = m;
        int half_len = (m + n + 1) / 2;

        while (imin <= imax) {
            int i = (imin + imax) / 2;
            int j = half_len - i;

            int nums1_left = (i == 0) ? INT_MIN : nums1[i - 1];
            int nums1_right = (i == m) ? INT_MAX : nums1[i];
            int nums2_left = (j == 0) ? INT_MIN : nums2[j - 1];
            int nums2_right = (j == n) ? INT_MAX : nums2[j];

            if (nums1_left <= nums2_right && nums2_left <= nums1_right) {
                if ((m + n) % 2 == 1) {
                    return std::max(nums1_left, nums2_left);
                } else {
                    return (std::max(nums1_left, nums2_left) + std::min(nums1_right, nums2_right)) / 2.0;
                }
            } else if (nums1_left > nums2_right) {
                imax = i - 1;
            } else {
                imin = i + 1;
            }
        }

        throw std::invalid_argument("Input arrays are not sorted!");
    }

};