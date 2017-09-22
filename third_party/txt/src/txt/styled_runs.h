/*
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIB_TXT_SRC_STYLED_RUNS_H_
#define LIB_TXT_SRC_STYLED_RUNS_H_

#include <list>
#include <vector>

#include "text_style.h"
#include "third_party/gtest/include/gtest/gtest_prod.h"

namespace txt {

// This holds and handles the start/end positions of discrete chunks of text
// that use different styles (a 'run').
class StyledRuns {
 public:
  struct Run {
    const TextStyle& style;
    size_t start;
    size_t end;
  };

  StyledRuns();

  ~StyledRuns();

  StyledRuns(const StyledRuns& other) = delete;

  StyledRuns(StyledRuns&& other);

  const StyledRuns& operator=(StyledRuns&& other);

  void swap(StyledRuns& other);

  size_t AddStyle(const TextStyle& style);

  // Returns the last TextStyle on the stack.
  const TextStyle& PeekStyle() const;

  void StartRun(size_t style_index, size_t start);

  void EndRunIfNeeded(size_t end);

  size_t size() const { return runs_.size(); }

  Run GetRun(size_t index) const;

  // Break any newline '\n' characters into their own runs.
  void SplitNewlineRuns(std::list<size_t> newline_positions);

 private:
  FRIEND_TEST(ParagraphTest, SimpleParagraph);
  FRIEND_TEST(ParagraphTest, SimpleRedParagraph);
  FRIEND_TEST(ParagraphTest, RainbowParagraph);
  FRIEND_TEST(ParagraphTest, DefaultStyleParagraph);
  FRIEND_TEST(ParagraphTest, BoldParagraph);
  FRIEND_TEST(ParagraphTest, LeftAlignParagraph);
  FRIEND_TEST(ParagraphTest, RightAlignParagraph);
  FRIEND_TEST(ParagraphTest, CenterAlignParagraph);
  FRIEND_TEST(ParagraphTest, JustifyAlignParagraph);
  FRIEND_TEST(ParagraphTest, DecorationsParagraph);
  FRIEND_TEST(ParagraphTest, ItalicsParagraph);
  FRIEND_TEST(ParagraphTest, ChineseParagraph);
  FRIEND_TEST(ParagraphTest, DISABLED_ArabicParagraph);
  FRIEND_TEST(ParagraphTest, LongWordParagraph);
  FRIEND_TEST(ParagraphTest, KernParagraph);
  FRIEND_TEST(ParagraphTest, HyphenBreakParagraph);
  FRIEND_TEST(ParagraphTest, RepeatLayoutParagraph);
  FRIEND_TEST(ParagraphTest, Ellipsize);

  struct IndexedRun {
    size_t style_index = 0;
    size_t start = 0;
    size_t end = 0;
  };

  std::vector<TextStyle> styles_;
  std::vector<IndexedRun> runs_;
};

}  // namespace txt

#endif  // LIB_TXT_SRC_STYLED_RUNS_H_