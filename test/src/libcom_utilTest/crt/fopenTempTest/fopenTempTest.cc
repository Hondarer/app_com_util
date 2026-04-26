#include <testfw.h>
#include <com_util/crt/stdio.h>
#include <com_util/crt/path.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>

#if defined(PLATFORM_LINUX)
    #include <unistd.h>
#elif defined(PLATFORM_WINDOWS)
    #include <io.h>
#endif /* PLATFORM_ */

class fopenTempTest : public Test
{
protected:
    static bool path_exists(const char *path)
    {
#if defined(PLATFORM_LINUX)
        return access(path, F_OK) == 0;
#elif defined(PLATFORM_WINDOWS)
        return _access(path, 0) == 0;
#endif /* PLATFORM_ */
    }

    static std::string basename_of(const std::string &path)
    {
        size_t pos = path.find_last_of("/\\");
        return (pos == std::string::npos) ? path : path.substr(pos + 1);
    }
};

TEST_F(fopenTempTest, opens_writable_file_and_reports_path)
{
    char  path[PLATFORM_PATH_MAX] = {};
    FILE *fp = com_util_fopen_temp("ptr", path, sizeof(path), nullptr);

    ASSERT_NE((FILE *)nullptr, fp);  // [確認_正常系] - FILE* が返ること。
    EXPECT_NE('\0', path[0]);        // [確認_正常系] - path_out が空文字列でないこと。

    const char data[] = "hello-temp";
    EXPECT_EQ(sizeof(data), fwrite(data, 1, sizeof(data), fp));
    EXPECT_EQ(0, fclose(fp));

    EXPECT_TRUE(path_exists(path));  // [確認_正常系] - 戻されたパスにファイルが実在すること。
    std::remove(path);
}

TEST_F(fopenTempTest, returns_unique_paths_for_repeated_calls)
{
    std::set<std::string> seen;
    for (int i = 0; i < 4; ++i)
    {
        char  path[PLATFORM_PATH_MAX] = {};
        FILE *fp = com_util_fopen_temp("ptr", path, sizeof(path), nullptr);
        ASSERT_NE((FILE *)nullptr, fp);
        fclose(fp);
        EXPECT_TRUE(seen.insert(path).second);  // [確認_正常系] - 過去に返された path と重複しないこと。
        std::remove(path);
    }
}

TEST_F(fopenTempTest, prefix_is_part_of_basename)
{
    char  path[PLATFORM_PATH_MAX] = {};
    FILE *fp = com_util_fopen_temp("abc", path, sizeof(path), nullptr);
    ASSERT_NE((FILE *)nullptr, fp);
    fclose(fp);

    std::string base = basename_of(path);
    EXPECT_NE(std::string::npos, base.find("abc"));  // [確認_正常系] - basename に prefix が含まれること。
    std::remove(path);
}

TEST_F(fopenTempTest, null_prefix_is_accepted)
{
    char  path[PLATFORM_PATH_MAX] = {};
    FILE *fp = com_util_fopen_temp(nullptr, path, sizeof(path), nullptr);
    ASSERT_NE((FILE *)nullptr, fp);  // [確認_正常系] - prefix=NULL でも FILE* が返ること。
    fclose(fp);
    std::remove(path);
}

TEST_F(fopenTempTest, null_path_out_returns_einval)
{
    int err = 0;
    FILE *fp = com_util_fopen_temp("ptr", nullptr, 0u, &err);
    EXPECT_EQ((FILE *)nullptr, fp);  // [確認_異常系] - NULL path_out で NULL が返ること。
    EXPECT_EQ(EINVAL, err);          // [確認_異常系] - errno_out に EINVAL が格納されること。
}

TEST_F(fopenTempTest, zero_path_size_returns_einval)
{
    char path[1] = { 'x' };
    int  err     = 0;
    FILE *fp = com_util_fopen_temp("ptr", path, 0u, &err);
    EXPECT_EQ((FILE *)nullptr, fp);  // [確認_異常系] - path_size=0 で NULL が返ること。
    EXPECT_EQ(EINVAL, err);          // [確認_異常系] - errno_out に EINVAL が格納されること。
}

#if defined(PLATFORM_LINUX)
TEST_F(fopenTempTest, path_size_too_small_returns_enametoolong)
{
    /* "<dir>/<prefix>XXXXXX" + NUL に満たない長さ */
    char path[4] = {};
    int  err     = 0;
    FILE *fp = com_util_fopen_temp("ptr", path, sizeof(path), &err);
    EXPECT_EQ((FILE *)nullptr, fp);   // [確認_異常系] - path_size が必要長未満で NULL が返ること。
    EXPECT_EQ(ENAMETOOLONG, err);     // [確認_異常系] - errno_out に ENAMETOOLONG が格納されること。
}
#endif /* PLATFORM_LINUX */

#if defined(PLATFORM_WINDOWS)
TEST_F(fopenTempTest, prefix_longer_than_three_chars_returns_einval)
{
    char path[PLATFORM_PATH_MAX] = {};
    int  err                      = 0;
    FILE *fp = com_util_fopen_temp("abcd", path, sizeof(path), &err);
    EXPECT_EQ((FILE *)nullptr, fp);  // [確認_異常系] - 4 文字以上の prefix で NULL が返ること。
    EXPECT_EQ(EINVAL, err);          // [確認_異常系] - errno_out に EINVAL が格納されること。
}
#endif /* PLATFORM_WINDOWS */
