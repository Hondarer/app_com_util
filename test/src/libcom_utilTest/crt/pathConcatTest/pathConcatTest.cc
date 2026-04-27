#include <testfw.h>
#include <com_util/crt/path.h>
#include <cerrno>
#include <cstring>

class pathConcatTest : public Test
{
};

TEST_F(pathConcatTest, concatenates_path_fragments)
{
    char path[PLATFORM_PATH_MAX] = {};
    int err = 0;

    EXPECT_EQ(0,
              com_util_path_concat(path, sizeof(path), &err,
                                   "tmp", PLATFORM_PATH_SEP, "libbase_extdef.txt"));
    EXPECT_STREQ("tmp/libbase_extdef.txt", path); // [確認_正常系] - 断片が指定順に連結されること。
}

TEST_F(pathConcatTest, keeps_empty_fragment)
{
    char path[32] = {};
    int err = 0;

    EXPECT_EQ(0, com_util_path_concat(path, sizeof(path), &err, "", "abc"));
    EXPECT_STREQ("abc", path); // [確認_正常系] - 空文字断片もそのまま扱えること。
}

TEST_F(pathConcatTest, accepts_sixteen_fragments)
{
    char path[32] = {};
    int err = 0;

    EXPECT_EQ(0,
              com_util_path_concat(path, sizeof(path), &err,
                                   "a", "b", "c", "d",
                                   "e", "f", "g", "h",
                                   "i", "j", "k", "l",
                                   "m", "n", "o", "p"));
    EXPECT_STREQ("abcdefghijklmnop", path); // [確認_正常系] - サポート上限の 16 断片を連結できること。
}

TEST_F(pathConcatTest, returns_einval_for_zero_part_count)
{
    char path[8] = {};
    int err = 0;

    EXPECT_EQ(-1, com_util_path_concat_n(path, sizeof(path), &err, 0u));
    EXPECT_EQ(EINVAL, err); // [確認_異常系] - part_count=0 で EINVAL が返ること。
}

TEST_F(pathConcatTest, returns_einval_for_null_fragment)
{
    char path[8] = {};
    int err = 0;

    EXPECT_EQ(-1, com_util_path_concat_n(path, sizeof(path), &err, 2u, "ab", (const char *)NULL));
    EXPECT_EQ(EINVAL, err); // [確認_異常系] - NULL 断片で EINVAL が返ること。
}

TEST_F(pathConcatTest, returns_enametoolong_when_result_does_not_fit)
{
    char path[5];
    int err = 0;

    std::memset(path, 'x', sizeof(path));

    EXPECT_EQ(-1, com_util_path_concat(path, sizeof(path), &err, "ab", "cd", "e"));
    EXPECT_EQ(ENAMETOOLONG, err); // [確認_異常系] - 末尾 NUL を含めて収まらない場合は ENAMETOOLONG が返ること。
    EXPECT_EQ('\0', path[0]);     // [確認_異常系] - 失敗時は空文字列に初期化されること。
}
