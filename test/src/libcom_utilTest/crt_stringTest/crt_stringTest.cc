#include <testfw.h>
#include <com_util/crt/string.h>
#include <errno.h>
#include <string.h>

class crt_stringTest : public Test
{
};

TEST_F(crt_stringTest, strcpy_success)
{
    char buf[16];

    int ret = com_util_strcpy(buf, sizeof(buf), "abc");

    EXPECT_EQ(0, ret);
    EXPECT_STREQ("abc", buf);
}

TEST_F(crt_stringTest, strcpy_null_argument)
{
    char buf[16];

    int ret = com_util_strcpy(buf, sizeof(buf), NULL);

    EXPECT_EQ(EINVAL, ret);
}

TEST_F(crt_stringTest, strcpy_buffer_shortage)
{
    char buf[3] = "xx";

    int ret = com_util_strcpy(buf, sizeof(buf), "abcd");

    EXPECT_EQ(ERANGE, ret);
    EXPECT_STREQ("", buf);
}

TEST_F(crt_stringTest, strncpy_truncates_to_count)
{
    char buf[8];

    int ret = com_util_strncpy(buf, sizeof(buf), "abcdef", 3);

    EXPECT_EQ(0, ret);
    EXPECT_STREQ("abc", buf);
}

TEST_F(crt_stringTest, strcat_success)
{
    char buf[16] = "abc";

    int ret = com_util_strcat(buf, sizeof(buf), "def");

    EXPECT_EQ(0, ret);
    EXPECT_STREQ("abcdef", buf);
}

TEST_F(crt_stringTest, sscanf_reads_three_tokens)
{
    char token1[8];
    char token2[8];
    char token3[8];

    int count = com_util_sscanf("one two three", "%7s %7s %7s", token1, token2, token3);

    EXPECT_EQ(3, count);
    EXPECT_STREQ("one", token1);
    EXPECT_STREQ("two", token2);
    EXPECT_STREQ("three", token3);
}

TEST_F(crt_stringTest, sscanf_returns_partial_count_for_short_input)
{
    char token1[8];
    char token2[8];
    char token3[8];

    int count = com_util_sscanf("one two", "%7s %7s %7s", token1, token2, token3);

    EXPECT_EQ(2, count);
}

TEST_F(crt_stringTest, sscanf_skips_repeated_spaces)
{
    char token1[8];
    char token2[8];
    char token3[8];

    int count = com_util_sscanf("  one   two\tthree", "%7s %7s %7s", token1, token2, token3);

    EXPECT_EQ(3, count);
    EXPECT_STREQ("one", token1);
    EXPECT_STREQ("two", token2);
    EXPECT_STREQ("three", token3);
}

TEST_F(crt_stringTest, sscanf_respects_width_limit)
{
    char token[4];

    int count = com_util_sscanf("abcdef", "%3s", token);

    EXPECT_EQ(1, count);
    EXPECT_STREQ("abc", token);
}
