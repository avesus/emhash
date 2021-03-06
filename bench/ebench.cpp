#include <random>
#include <map>
#include <ctime>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>

#if __cplusplus > 201402L || __clang__ || _MSC_VER >= 1600
//    #define STR_VIEW  1
    #include <string_view>
#endif

#ifdef __has_include
    #if __has_include("wyhash.h")
    #include "wyhash.h"
    #endif
#endif

#ifndef TKey
    #define TKey              1
#endif
#ifndef TVal
    #define TVal              1
#endif

static void printInfo(char* out);

//#define ET                     1
#if __x86_64__ || _M_X64 || _M_IX86 || __i386__
#define PHMAP_HAVE_SSSE3       1
#endif

//#define HOOD_HASH           1
//#define PHMAP_HASH          1
//#define EMH_WY_HASH         1
//#define FL1                 1

//#define EMH_BUCKET_INDEX    2
//#define EMH_REHASH_LOG  10345
//#define EMH_AVX_MEMCPY     1

//#define EMH_STATIS         1
//#define EMH_FIBONACCI_HASH  1
//#define EMH_SAFE_ITER         1
//#define EMH_SAFE_HASH        1
//#define EMH_IDENTITY_HASH   1

//#define EMH_LRU_SET        1
//#define EMH_STD_STRING     1
//#define EMH_ERASE_SMALL    1
//#define EMH_HIGH_LOAD        201000

//
#include "hash_table2.hpp"
#include "hash_table3.hpp"
#include "hash_table4.hpp"
#include "hash_table5.hpp"
#include "hash_table6.hpp"
#include "hash_table7.hpp"



//https://www.zhihu.com/question/46156495
//https://eourcs.github.io/LockFreeCuckooHash/
//https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
////some others
//https://sites.google.com/view/patchmap/overview
//https://github.com/ilyapopov/car-race
//https://hpjansson.org/blag/2018/07/24/a-hash-table-re-hash/
//https://www.reddit.com/r/cpp/comments/auwbmg/hashmap_benchmarks_what_should_i_add/
//https://www.youtube.com/watch?v=M2fKMP47slQ
//https://yq.aliyun.com/articles/563053

//https://engineering.fb.com/developer-tools/f14/
//https://github.com/facebook/folly/blob/master/folly/container/F14.md

//https://martin.ankerl.com/2019/04/01/hashmap-benchmarks-01-overview/
//https://martin.ankerl.com/2016/09/21/very-fast-hashmap-in-c-part-3/

//https://attractivechaos.wordpress.com/2018/01/13/revisiting-hash-table-performance/
//https://attractivechaos.wordpress.com/2019/12/28/deletion-from-hash-tables-without-tombstones/#comment-9548
//https://attractivechaos.wordpress.com/2008/08/28/comparison-of-hash-table-libraries/
//https://en.wikipedia.org/wiki/Hash_table
//https://tessil.github.io/2016/08/29/benchmark-hopscotch-map.html
//https://probablydance.com/2017/02/26/i-wrote-the-fastest-hashtable/
//https://andre.arko.net/2017/08/24/robin-hood-hashing/
//http://www.ilikebigbits.com/2016_08_28_hash_table.html
//http://www.idryman.org/blog/2017/05/03/writing-a-damn-fast-hash-table-with-tiny-memory-footprints/
//https://jasonlue.github.io/algo/2019/08/27/clustered-hashing-basic-operations.html
//https://bigdata.uni-saarland.de/publications/p249-richter.pdf

#if HOOD_HASH
    #include "martin/robin_hood.h"    //https://github.com/martin/robin-hood-hashing/blob/master/src/include/robin_hood.h
#elif PHMAP_HASH
    #include "phmap/phmap.h"    //https://github.com/martin/robin-hood-hashing/blob/master/src/include/robin_hood.h
#endif

#if ET
    #define  _CPP11_HASH    1

#if __x86_64__ || _WIN64
    #include "hrd/hash_set7.h"        //https://github.com/hordi/hash/blob/master/include/hash_set7.h
    #include "emilib/hash_emilib33.hpp"
    #include "ska/bytell_hash_map.hpp"//https://github.com/skarupke/flat_hash_map/blob/master/bytell_hash_map.hpp
    #include "ska/flat_hash_map.hpp"  //https://github.com/skarupke/flat_hash_map/blob/master/flat_hash_map.hpp
#endif
    #include "lru_size.h"
    #include "lru_time.h"
    #include "phmap/btree.h"          //https://github.com/greg7mdp/parallel-hashmap/tree/master/parallel_hashmap
#if ET > 1
    #include "tsl/robin_map.h"        //https://github.com/tessil/robin-map
    #include "tsl/hopscotch_map.h"    //https://github.com/tessil/hopscotch-map
#endif

    #include "phmap/phmap.h"          //https://github.com/greg7mdp/parallel-hashmap/tree/master/parallel_hashmap
    #include "martin/robin_hood.h"    //https://github.com/martin/robin-hood-hashing/blob/master/src/include/robin_hood.h
#endif

#include <unordered_map>

#ifdef _WIN32
    # define CONSOLE "CON"
    # include <windows.h>
#else
    # define CONSOLE "/dev/tty"
    # include <unistd.h>
    # include <sys/resource.h>
    # include <sys/time.h>
#endif

#ifndef PACK
#define PACK 128
#endif
struct StructValue
{
    StructValue(int64_t i = 0)
    {
        lScore = i;
        lUid = 0;
        iRank = iUpdateTime = 0;
    }

    bool operator == (const StructValue& v) const
    {
        return v.lScore == lScore;
    }

    int64_t operator ()() const
    {
        return lScore;
    }

    int64_t lUid;
    int64_t lScore;
    int  iUpdateTime;
    int  iRank;

#if PACK >= 24
    char data[(PACK - 24) / 8 * 8];
#endif

#if COMP
    std::string sdata = {"test data input"};
    std::vector<int> vint = {1,2,3,4,5,6,7,8};
    std::map<std::string, int> msi = {{"111", 1}, {"1222", 2}};
#endif
};

struct StuHasher
{
    std::size_t operator()(const StructValue& v) const
    {
        return v.lScore * 11400714819323198485ull;
    }
};

#if BAD_HASH > 100
template <typename KeyT>
struct BadHasher
{
    std::size_t operator()(const KeyT& v) const
    {
#if 1
        return v % BAD_HASH;
#else
        return v.size();
#endif
    }
};
#endif

struct WysHasher
{
    std::size_t operator()(const std::string& str) const
    {
#ifdef WYHASH_LITTLE_ENDIAN
        return wyhash(str.c_str(), str.size(), 0x123456789 + str.size());
#else
        size_t hash = 0;
        for (const auto c : str)
            hash = c + hash * 131;
        return hash;
#endif
    }
};

#if TKey == 0
    typedef unsigned int keyType;
    #define TO_KEY(i)   (keyType)i
    #define sKeyType    "int"
    #define KEY_INT     1
#elif TKey == 1
    typedef int64_t      keyType;
    #define TO_KEY(i)   (keyType)i
    #define sKeyType    "int64_t"
    #define KEY_INT     1
#elif TKey == 2
    #define KEY_STR     1
    typedef std::string keyType;
    #define TO_KEY(i)   std::to_string(i)
    #define sKeyType    "string"
#elif TKey == 3
    #define KEY_SUC    1
    typedef StructValue keyType;
    #define TO_KEY(i)   StructValue((int64_t)i)
    #define sKeyType    "Struct"
#else
    #define KEY_STR     1
    typedef std::string_view keyType;
    #define TO_KEY(i)   std::to_string(i)
    #define sKeyType    "string_view"
#endif

#if TVal == 0
    typedef int         valueType;
    #define TO_VAL(i)   i
    #define TO_SUM(i)   i
    #define sValueType  "int"
#elif TVal == 1
    typedef int64_t     valueType;
    #define TO_VAL(i)   i
    #define TO_SUM(i)   i
    #define sValueType  "int64_t"
#elif TVal == 2
    typedef std::string valueType;
    #define TO_VAL(i)   #i
    #define TO_SUM(i)   i.size()
    #define sValueType  "string"
#elif TValue == 3
    typedef std::string_view valueType;
    #define TO_VAL(i)   #i
    #define TO_SUM(i)   i.size()
    #define sValueType  "string_view"
#else
    typedef StructValue valueType;
    #define TO_VAL(i)   i
    #define TO_SUM(i)   i.lScore
    #define sValueType  "Struct"
#endif

emhash2::HashMap<std::string, std::string> hash_tables =
{
//    {"stl_hash", "unordered_map"},
    {"stl_map", "stl_map"},
    {"btree", "btree_map"},

    {"emhash2", "emhash2"},
    {"emhash3",  "emhash3"},
    {"emhash4", "emhash4"},

    {"emhash5", "emhash5"},
    {"emhash6", "emhash6"},
    {"emhash7", "emhash7"},

    {"lru_time", "lru_time"},
    {"lru_size", "lru_size"},

    {"emilib2", "emilib2"},
    {"emilib4", "emilib4"},
    {"emilib3", "emilib3"},
//    {"ktprime", "ktprime"},

#if ET
    {"martin", "martin_flat"},
    {"phmap", "phmap_flat"},
    {"hrdset",   "hrdset"},

    {"robin", "tsl_robin"},
    {"flat", "ska_flat"},

    {"hopsco", "tsl_hopsco"},
    {"byte", "ska_byte"},
#endif
};

static int64_t getTime()
{
#if WIN32_RSU
    FILETIME ptime[4] = {0, 0, 0, 0, 0, 0, 0, 0};
    GetThreadTimes(GetCurrentThread(), NULL, NULL, &ptime[2], &ptime[3]);
    return (ptime[2].dwLowDateTime + ptime[3].dwLowDateTime) / 10;
#elif WIN32_TICK
    return GetTickCount() * 1000;
#elif _WIN32
    static LARGE_INTEGER freq = {0};
    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }

    LARGE_INTEGER nowus;
    QueryPerformanceCounter(&nowus);
    return (nowus.QuadPart * 1000000) / (freq.QuadPart);
#elif LINUX_RUS
    struct rusage rup;
    getrusage(RUSAGE_SELF, &rup);
    long sec  = rup.ru_utime.tv_sec  + rup.ru_stime.tv_sec;
    long usec = rup.ru_utime.tv_usec + rup.ru_stime.tv_usec;
    return sec * 1000000 + usec;
#elif LINUX_TICK || __APPLE__
    return clock();
#elif __linux__ || __unix__
    struct timeval start;
    gettimeofday(&start, NULL);
    return start.tv_sec * 1000000l + start.tv_usec;
#endif
}

static int ilog(int x, const int n = 2)
{
    int logn = 0;
    while (x / n) {
        logn ++;
        x /= n;
    }

    return logn;
}

uint64_t randomseed() {
    std::random_device rd;
    return std::uniform_int_distribution<uint64_t>{}(rd);
}
// this is probably the fastest high quality 64bit random number generator that exists.
// Implements Small Fast Counting v4 RNG from PractRand.
class sfc64 {
public:
    using result_type = uint64_t;

    sfc64()
        : sfc64(randomseed()) {}

    sfc64(uint64_t a, uint64_t b, uint64_t c, uint64_t counter)
        : m_a{ a }
        , m_b{ b }
        , m_c{ c }
        , m_counter{ counter } {}

    sfc64(std::array<uint64_t, 4> const& state)
        : m_a{ state[0] }
        , m_b{ state[1] }
        , m_c{ state[2] }
        , m_counter{ state[3] } {}

    explicit sfc64(uint64_t seed)
        : m_a(seed)
        , m_b(seed)
        , m_c(seed)
        , m_counter(1) {
        for (int i = 0; i < 12; ++i) {
            operator()();
        }
    }

    // no copy ctors so we don't accidentally get the same random again
    sfc64(sfc64 const&) = delete;
    sfc64& operator=(sfc64 const&) = delete;

    sfc64(sfc64&&) = default;
    sfc64& operator=(sfc64&&) = default;

    ~sfc64() = default;

    static constexpr uint64_t(min)() {
        return (std::numeric_limits<uint64_t>::min)();
    }
    static constexpr uint64_t(max)() {
        return (std::numeric_limits<uint64_t>::max)();
    }

    void seed() {
        seed(randomseed());
    }

    void seed(uint64_t seed) {
        state(sfc64{ seed }.state());
    }

    uint64_t operator()() noexcept {
        auto const tmp = m_a + m_b + m_counter++;
        m_a = m_b ^ (m_b >> right_shift);
        m_b = m_c + (m_c << left_shift);
        m_c = rotl(m_c, rotation) + tmp;
        return tmp;
    }

    template <typename T>
    T uniform(T input) {
        return static_cast<T>(operator()(static_cast<uint64_t>(input)));
    }

    template <typename T>
    T uniform() {
        return static_cast<T>(operator()());
    }

    // Uses the java method. A bit slower than 128bit magic from
    // https://arxiv.org/pdf/1805.10941.pdf, but produces the exact same results in both 32bit and
    // 64 bit.
    uint64_t operator()(uint64_t boundExcluded) noexcept {
        uint64_t x, r;
        do {
            x = operator()();
            r = x % boundExcluded;
        } while (x - r > (UINT64_C(0) - boundExcluded));
        return r;
    }

    std::array<uint64_t, 4> state() const {
        return { {m_a, m_b, m_c, m_counter} };
    }

    void state(std::array<uint64_t, 4> const& s) {
        m_a = s[0];
        m_b = s[1];
        m_c = s[2];
        m_counter = s[3];
    }

private:
    template <typename T>
    T rotl(T const x, size_t k) {
        return (x << k) | (x >> (8 * sizeof(T) - k));
    }

    static constexpr size_t rotation = 24;
    static constexpr size_t right_shift = 11;
    static constexpr size_t left_shift = 3;
    uint64_t m_a;
    uint64_t m_b;
    uint64_t m_c;
    uint64_t m_counter;
};

#include <chrono>
static const std::array<char, 62> ALPHANUMERIC_CHARS = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

std::uniform_int_distribution<std::size_t> rd_uniform(0, ALPHANUMERIC_CHARS.size() - 1);

#ifdef KEY_STR
static std::mt19937_64 generator(time(0));
static std::string get_random_alphanum_string(std::size_t size) {
    std::string str(size, '\0');

    const auto comm_head = size % 4 + 1;
    //test common head
    for(std::size_t i = 0; i < comm_head; i++) {
        str[i] = ALPHANUMERIC_CHARS[i];
    }
    for(std::size_t i = comm_head; i < size; i++) {
        str[i] = ALPHANUMERIC_CHARS[rd_uniform(generator)];
    }

    return str;
}
#endif

static int tcase = 0;
static int loop_vector_time = 0;
static int func_index = 1, func_print = 0;
static std::map<std::string, size_t> check_result;
//func --> hash time
static std::map<std::string, std::map<std::string, int64_t>> once_func_hash_time;


static void check_func_result(const std::string& hash_name, const std::string& func, size_t sum, int64_t ts1, int weigh = 1)
{
    if (check_result.find(func) == check_result.end()) {
        check_result[func] = sum;
    } else if (sum != check_result[func]) {
        printf("%s %s %zd != %zd (o)\n", hash_name.c_str(), func.c_str(), sum, check_result[func]);
    }

    auto& showname = hash_tables[hash_name];
    once_func_hash_time[func][showname] += (getTime() - ts1 - loop_vector_time / 8) / weigh;
    func_index ++;

    int ts = (getTime() - ts1) / 1000;
    if (func_index == func_print)
        printf("%8s: %8s %4d, ",hash_name.data(), func.c_str(), ts);
    else if (func_index == func_print + 1)
        printf("%8s %4d, ", func.c_str(), ts);
    else if (func_index == func_print + 2)
        printf("%8s %4d, ", func.c_str(), ts);
    else if (func_index == func_print + 3)
        printf("%8s %4d\n", func.c_str(), ts);
}

static void inline hash_convert(const std::map<std::string, int64_t>& hash_time, std::multimap <int64_t, std::string>& time_hash)
{
    for (const auto& v : hash_time)
        time_hash.insert(std::pair<int64_t, std::string>(v.second, v.first));
}

static void add_hash_func_time(std::map<std::string, std::map<std::string, int64_t>>& func_hash_time, std::multimap <int64_t, std::string>& once_time_hash)
{
    std::map<std::string, int64_t> once_hash_time;
    for (auto& v : once_func_hash_time) {
        for (auto& f : v.second) {
            func_hash_time[v.first][f.first] += f.second;
            once_hash_time[f.first] += f.second;
        }
    }
    hash_convert(once_hash_time, once_time_hash);
}

static void dump_func(const std::string& func, const std::map<std::string, int64_t >& hash_rtime, std::map<std::string, int64_t>& hash_score, std::map<std::string, std::map<std::string, int64_t>>& hash_func_time)
{
    std::multimap <int64_t, std::string> rtime_hash;
    hash_convert(hash_rtime, rtime_hash);

    puts(func.c_str());

    auto min = rtime_hash.begin()->first + 1;
    for (auto& v : rtime_hash) {
        hash_score[v.second] += (int)((min * 100) / (v.first + 0));

        //hash_func_time[v.second][func] = (int)((min * 100) / (v.first + 1));
        hash_func_time[v.second][func] = v.first / 10000;
        printf("   %-8d     %-21s   %02d\n", (int)(v.first / 10000), v.second.c_str(), (int)((min * 100) / (v.first + 0)));
    }
    putchar('\n');
}

static void dump_all(std::map<std::string, std::map<std::string, int64_t>>& func_rtime, std::multimap<int64_t, std::string>& score_hash)
{
    std::map<std::string, int64_t> hash_score;
    std::map<std::string, std::map<std::string, int64_t>> hash_func_time;
    for (const auto& v : func_rtime) {
        dump_func(v.first, v.second, hash_score, hash_func_time);
    }
    hash_convert(hash_score, score_hash);

    if (tcase % 100 != 0)
        return;

    std::string pys =
    "import numpy as np\n"
    "import matplotlib.pyplot as plt\n\n"
    "def autolabel(rects):\n"
        "\tfor rect in rects:\n"
        "\t\twidth = rect.get_width()\n"
        "\t\tplt.text(width + 1.0, rect.get_y(), '%s' % int(width))\n\n"
    "divisions = [";

    pys.reserve(2000);
    for (const auto& v : func_rtime) {
        pys += "\"" + v.first + "\",";
    }

    pys.back() = ']';
    pys += "\n\n";

    auto hash_size = hash_func_time.size();
    auto func_size = func_rtime.size();

    pys += "plt.figure(figsize=(14," + std::to_string(func_size) + "))\n";
    pys += "index = np.arange(" + std::to_string(func_size) + ")\n";
    if (hash_size > 4)
        pys += "width = " + std::to_string(0.8 / hash_size) + "\n\n";
    else
        pys += "width = 0.20\n\n";

    std::string plt;
    int id = 0;
    static std::vector<std::string> colors = {
        "cyan", "magenta",
        "green", "red", "blue", "yellow", "black", "orange", "brown", "grey", "pink",
        "#eeefff", "burlywood",
    };

    for (auto& kv : hash_func_time) {
        pys += kv.first + "= [";
        for (auto& vk : kv.second) {
            pys += std::to_string(vk.second) + ",";
        }
        pys.back() = ']';
        pys += "\n";

        plt += "a" + std::to_string(id + 1) + " = plt.barh(index + width * " + std::to_string(id) + "," + kv.first +
            ",width, label = \"" + kv.first + "\")\n";
        plt += "autolabel(a" + std::to_string(id + 1) + ")\n\n";
        id ++;
    }

    //os
    char os_info[2048]; printInfo(os_info);

    pys += "\n" + plt + "\n";
    auto file = std::string(sKeyType) + "_" + sValueType;
    pys += std::string("file = \"") + file + ".png\"\n\n";
    pys += std::string("plt.title(\"") + file + "-" + std::to_string(tcase) + "\")\n";
    pys +=
        "plt.xlabel(\"performance\")\n"
        "plt.xlabel(\"" + std::string(os_info) + "\")\n"
        "plt.yticks(index + width / 2, divisions)\n"
        "plt.legend()\n"
        "plt.show()\n"
        "plt.savefig(file)\n";

    pys += std::string("\n\n# ") + os_info;

    //puts(pys.c_str());
    std::ofstream  outfile;
    auto full_file = file + ".py";
    outfile.open("./" + full_file, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    if (outfile.is_open())
        outfile << pys;
    else
        printf("\n\n =============== can not open %s ==============\n\n", full_file.c_str());

    outfile.close();
}

template<class hash_type>
void hash_iter(const hash_type& ahash, const std::string& hash_name)
{
    auto ts1 = getTime(); size_t sum = 0;
    for (auto& v : ahash)
        sum += TO_SUM(v.second);

    for (auto it = ahash.cbegin(); it != ahash.cend(); ++it)
#if KEY_INT
        sum += it->first;
#elif KEY_SUC
    sum += it->first.lScore;
#else
    sum += it->first.size();
#endif
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void erase_reinsert(hash_type& ahash, const std::string& hash_name, std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList) {
        ahash[v] = TO_VAL(0);
#if TVal < 2
        sum += ahash.count(v);
#else
        sum += TO_SUM(ahash[v]);
#endif
    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void insert_no_reserve( const std::string& hash_name, const std::vector<keyType>& vList)
{
    hash_type ahash;
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList)
        sum += ahash.emplace(v, TO_VAL(0)).second;
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void insert_reserve(hash_type& ahash, const std::string& hash_name, const std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
#ifndef SMAP
    ahash.reserve(vList.size());
    ahash.max_load_factor(0.99f);
#endif

    for (const auto& v : vList)
        sum += ahash.insert_or_assign(v, TO_VAL(0)).second;
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void find_insert_multi(const std::string& hash_name, const std::vector<keyType>& vList)
{
#if KEY_INT
    size_t sum = 0;
    constexpr auto hash_size = 65437;
    auto mh = new hash_type[hash_size];

    auto ts1 = getTime();
    for (const auto& v : vList) {
        auto hash_id = ((uint64_t)v) % hash_size;
        sum += mh[hash_id].emplace(v, TO_VAL(0)).second;
    }

    for (const auto& v : vList) {
        auto hash_id = ((uint64_t)v) % hash_size;
        sum += mh[hash_id].count(v + v % 2);
    }

    int last =(int)mh[0].size();
    delete []mh;
    check_func_result(hash_name, __FUNCTION__, sum, ts1, 2);
#endif
}

template<class hash_type>
void insert_find_erase(const hash_type& ahash, const std::string& hash_name, std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
    hash_type tmp(ahash);

    for (auto & v : vList) {
#if KEY_INT
        auto v2 = v / 101 + v;
#elif KEY_SUC
        auto v2(v.lScore / 101 + v.lScore);
#elif TKey != 4
        v += char(128 + (int)v[0]);
        const auto &v2 = v;
#else
        const keyType v2(v.data(), v.size() - 1);
#endif
        sum += tmp.emplace(v2, TO_VAL(0)).second;
        sum += tmp.count(v2);
        sum += tmp.erase(v2);
    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1, 3);
}

template<class hash_type>
void insert_cache_size(const std::string& hash_name, const std::vector<keyType>& vList, const char* level, const uint32_t min_size, const uint32_t cache_size)
{
    auto ts1 = getTime(); size_t sum = 0;
    const auto smalls = min_size + vList.size() % cache_size;
    hash_type tmp, empty;
#ifndef SMAP
    empty.max_load_factor(0.875);
#endif
    tmp = empty;

    for (const auto& v : vList)
    {
        sum += tmp.emplace(v, TO_VAL(0)).second;
        //sum += tmp.count(v);
        if (tmp.size() > smalls) {
            if (smalls % 2 == 0)
                tmp.clear();
            else
                tmp = empty;
        }
    }
    check_func_result(hash_name, level, sum, ts1);
}

template<class hash_type>
void insert_high_load(const std::string& hash_name, const std::vector<keyType>& vList)
{
    size_t sum = 0;
    size_t pow2 = 2u << ilog(vList.size(), 2);
    hash_type tmp;

    const auto max_loadf = 0.99f;
#ifndef SMAP
    tmp.reserve(pow2 / 2);
    tmp.max_load_factor(max_loadf);
#endif
    int minn = (max_loadf - 0.2f) * pow2, maxn = max_loadf * pow2;
    int i = 0;

    for (; i < minn; i++) {
        if (i < (int)vList.size())
            tmp.emplace(vList[i], TO_VAL(0));
        else {
            auto& v = vList[i - vList.size()];
#if KEY_INT
            auto v2 = v + (v / 11) + i;
#elif KEY_SUC
            auto v2 = v.lScore + (v.lScore / 11) + i;
#elif TKey != 4
            auto v2 = v; v2[0] += '2';
#else
            const keyType v2(v.data(), v.size() - 1);
#endif
            tmp.emplace(v2, TO_VAL(0));
        }
    }

    auto ts1 = getTime();
    for (; i  < maxn; i++) {
        auto& v = vList[i - minn];
#if KEY_INT
        auto v2 = (v / 7) + 4 * v;
#elif KEY_SUC
        auto v2 = (v.lScore / 7) + 4 * v.lScore;
#elif TKey != 4
        auto v2 = v; v2[0] += '1';
#else
        const keyType v2(v.data(), v.size() - 1);
#endif
        tmp[v2] = TO_VAL(0);
        sum += tmp.count(v2);
    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

static uint8_t l1_cache[64 * 1024];
template<class hash_type>
void find_miss_all(hash_type& ahash, const std::string& hash_name)
{
    auto ts1 = getTime();
    auto n = ahash.size();
    size_t pow2 = 2u << ilog(n, 2), sum = 0;

#if KEY_STR
    std::string skey = get_random_alphanum_string(40);
#endif

    for (size_t v = 1; v < pow2; v++) {
#if FL1
        l1_cache[v % sizeof(l1_cache)] = 0;
#endif
#if KEY_STR
        skey[v % 32 + 1] ++;
        sum += ahash.count((const char*)skey.c_str());
#else
        sum += ahash.count(TO_KEY(v));
#endif
    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void find_hit_half(hash_type& ahash, const std::string& hash_name, const std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList) {
#if FL1
        if (sum % (1024 * 256) == 0)
            memset(l1_cache, 0, sizeof(l1_cache));
#endif
        sum += ahash.count(v);
    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void find_hit_all(const hash_type& ahash, const std::string& hash_name, const std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList) {
#if KEY_INT
        sum += ahash.count(v) + v;
#elif KEY_SUC
        sum += ahash.count(v) + v.lScore;
#else
        sum += ahash.count(v) + v.size();
#endif
#if FL1
        if (sum % (1024 * 64) == 0)
            memset(l1_cache, 0, sizeof(l1_cache));
#endif

    }
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void erase_find_half(const hash_type& ahash, const std::string& hash_name, const std::vector<keyType>& vList)
{
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList)
        sum += ahash.count(v);
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void erase_half(hash_type& ahash, const std::string& hash_name, const std::vector<keyType>& vList)
{
    auto tmp = ahash;
    auto ts1 = getTime(); size_t sum = 0;
    for (const auto& v : vList)
        sum += ahash.erase(v);

    for (auto it = tmp.begin(); it != tmp.end(); ) {
        it = tmp.erase(it);
        sum += 1;
    }

    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void hash_clear(hash_type& ahash, const std::string& hash_name)
{
    auto ts1 = getTime();
    size_t sum = ahash.size();
    ahash.clear(); ahash.clear();
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

template<class hash_type>
void hash_copy(hash_type& ahash, const std::string& hash_name)
{
    size_t sum = 0;
    auto ts1 = getTime();
    hash_type thash = ahash;
    ahash = thash;
    ahash = std::move(thash);
    sum  = thash.size();
    check_func_result(hash_name, __FUNCTION__, sum, ts1);
}

#if PACK >= 24
static_assert(sizeof(StructValue) == PACK, "PACK >=24");
#endif

template<class RandomIt>
void shuffle(RandomIt first, RandomIt last)
{
    std::random_device rd;
    std::mt19937 g(rd());
    typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
    typedef std::uniform_int_distribution<diff_t> distr_t;
    typedef typename distr_t::param_type param_t;

    distr_t D;
    diff_t n = last - first;
    for (diff_t i = n-1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[D(g, param_t(0, i))]);
    }
}

//https://en.wikipedia.org/wiki/Gamma_distribution#/media/File:Gamma_distribution_pdf.svg
//https://blog.csdn.net/luotuo44/article/details/33690179
static int buildTestData(int size, std::vector<keyType>& randdata)
{
    randdata.reserve(size);

#if 1
    sfc64 srng(size);
#else
    std::mt19937_64 srng; srng.seed(size);
#endif

#ifdef KEY_STR
    for (int i = 0; i < size; i++)
        randdata.emplace_back(get_random_alphanum_string(srng() % 64 + 8));
    return 0;
#else

#if AR > 0
    const auto iRation = AR;
#else
    const auto iRation = 1;
#endif

    auto flag = 0;
    if (srng() % 100 > iRation)
    {
        for (int i = 0; ; i++) {
            auto key = TO_KEY(srng());
            randdata.emplace_back(key);
            if (randdata.size() >= size)
                break;
        }
    }
    else
    {
        flag = srng() % 5 + 1;
        const auto pow2 = 2u << ilog(size, 2);
        auto k = srng();
        for (int i = 1; i <= size; i ++) {
            k ++;
            if (flag == 2)
                k += (1 << 8) - 1;
            else if (flag == 3) {
                k += pow2 + 32 - srng() % 64;
                if (srng() % 64 == 0)
                    k += 80;
            }
            else if (flag == 4) {
                if (srng() % 32 == 0)
                    k += 32;
            } else if (flag == 5) {
                k = i * (uint64_t)pow2 + srng() % (pow2 / 8);
            }

            randdata.emplace_back(k);
        }
    }

    return flag;
#endif
}

static int TestHashMap(int n, int max_loops = 1234567)
{
#ifndef KEY_SUC
    emhash5::HashMap <keyType, int> ehash5;
    emhash6::HashMap <keyType, int> ehash2;

    sfc64 srng(time(NULL));
#if ET
    robin_hood::unordered_flat_map<keyType, int> unhash;
#else
    std::unordered_map<long,int> unhash;
#endif

    const auto step = n % 2 + 1;
    for (int i = 1; i < n * step; i += step) {
        auto ki = TO_KEY(i);
        ehash5[ki] = unhash[ki] = ehash2[ki] = (int)srng();
    }

    int loops = max_loops;
    while (loops -- > 0) {
        assert(ehash2.size() == unhash.size()); assert(ehash5.size() == unhash.size());

        const uint32_t type = srng() % 100;
        auto rid  = n ++;
        auto id   = TO_KEY(rid);
        if (type <= 40 || ehash2.size() < 1000) {
            ehash2[id] += type; ehash5[id] += type; unhash[id]  += type;

            assert(ehash2[id] == unhash[id]); assert(ehash5[id] == unhash[id]);
        }
        else if (type < 60) {
            if (srng() % 3 == 0)
                id = unhash.begin()->first;
            else if (srng() % 2 == 0)
                id = ehash2.begin()->first;
            else
                id = ehash5.begin()->first;

            ehash5.erase(ehash5.find(id));
            unhash.erase(id);
            ehash2.erase(id);

            assert(ehash5.count(id) == unhash.count(id));
            assert(ehash2.count(id) == unhash.count(id));
        }
        else if (type < 80) {
            auto it = ehash5.begin();
            for (int i = n % 64; i > 0; i--)
                it ++;
            id = it->first;
            unhash.erase(id);
            ehash2.erase(ehash2.find(id));
            ehash5.erase(it);
            assert(ehash2.count(id) == 0);
            assert(ehash5.count(id) == unhash.count(id));
        }
        else if (type < 100) {
            if (unhash.count(id) == 0) {
                const auto vid = (int)rid;
                ehash5.emplace(id, vid);
                assert(ehash5.count(id) == 1);
                assert(ehash2.count(id) == 0);

                //if (id == 1043)
                ehash2.insert(id, vid);
                assert(ehash2.count(id) == 1);

                unhash[id] = ehash2[id];
                assert(unhash[id] == ehash2[id]);
                assert(unhash[id] == ehash5[id]);
            } else {
                unhash[id] = ehash2[id] = ehash5[id] = 1;
                unhash.erase(id);
                ehash2.erase(id);
                ehash5.erase(id);
            }
        }
        if (loops % 100000 == 0) {
            printf("%d %d\r", loops, (int)ehash2.size());
#ifdef KEY_INT
            ehash2.shrink_to_fit();
            //ehash5.shrink_to_fit();

            uint64_t sum1 = 0, sum2 = 0, sum3 = 0;
            for (auto v : unhash) sum1 += v.first * v.second;
            for (auto v : ehash2) sum2 += v.first * v.second;
            for (auto v : ehash5) sum3 += v.first * v.second;
            assert(sum1 == sum2);
            assert(sum1 == sum3);
#endif
        }
    }

    printf("\n");
#endif
    return 0;
}

template<class hash_type>
int benOneHash(const std::string& hash_name, const std::vector<keyType>& oList)
{
    if (hash_tables.find(hash_name) == hash_tables.end())
        return 0;

    float load_factor = 0;

    if (tcase == 0)
        printf("bench %s:%zd\n", hash_name.data(), sizeof(hash_type));

    {
        hash_type hash;
        const uint32_t l1_size = (64 * 1024)   / (sizeof(keyType) + sizeof(valueType) + sizeof(int));
        const uint32_t l3_size = (8 * 1024 * 1024) / (sizeof(keyType) + sizeof(valueType) + sizeof(int));

        func_index  = 0;
        insert_high_load  <hash_type>(hash_name, oList);
        insert_cache_size <hash_type>(hash_name, oList, "insert_l1_cache", l1_size / 2, 2 * l1_size + 1000);
        insert_cache_size <hash_type>(hash_name, oList, "insert_l3_cache", l1_size * 4, l3_size);
        insert_no_reserve <hash_type>(hash_name, oList);
        find_insert_multi <hash_type>(hash_name, oList);

        insert_reserve<hash_type>(hash,hash_name, oList);
        find_hit_all  <hash_type>(hash, hash_name,oList);
        find_miss_all <hash_type>(hash, hash_name);

        auto vList = oList;
        for (size_t v = 0; v < vList.size() / 2; v++) {
#if KEY_INT
            vList[v] += v * v + v;
#elif KEY_SUC
            vList[v].lScore += v * v;
#elif TKey != 4
            vList[v][0] += 1;
#else
            auto& next2 = vList[v + vList.size() / 2];
            vList[v] = next2.substr(0, next2.size() - 1);
#endif
        }

        find_hit_half<hash_type>(hash, hash_name, vList);
        erase_half<hash_type>(hash, hash_name, vList);
        erase_find_half<hash_type>(hash, hash_name, vList);
        erase_reinsert<hash_type>(hash, hash_name, vList);
        insert_find_erase<hash_type>(hash, hash_name, vList);

#ifndef SMAP
        load_factor = hash.load_factor() * 100.0;
#endif
        hash_iter<hash_type>(hash, hash_name);

#ifdef UF
        hash_copy<hash_type>(hash, hash_name);
        hash_clear<hash_type>(hash, hash_name);
#endif
    }

    return load_factor;
}

constexpr auto base1 = 300000000;
constexpr auto base2 =      20000;
void reset_top3(std::map<std::string, int64_t>& top3, const std::multimap <int64_t, std::string>& once_time_hash)
{
    auto it0 = once_time_hash.begin();
    auto it1 = *(it0++);
    auto it2 = *(it0++);
    auto it3 = *(it0++);

    //the top 3 func map
    if (it1.first == it3.first) {
        top3[it1.second] += base1 / 3;
        top3[it2.second] += base1 / 3;
        top3[it3.second] += base1 / 3;
    } else if (it1.first == it2.first) {
        top3[it1.second] += base1 / 2;
        top3[it2.second] += base1 / 2;
        top3[it3.second] += 1;
    } else {
        top3[it1.second] += base1;
        if (it2.first == it3.first) {
            top3[it2.second] += base2 / 2;
            top3[it3.second] += base2 / 2;
        } else {
            top3[it2.second] += base2;
            top3[it3.second] += 1;
        }
    }
}

static void printResult(int vsize)
{
    //total func hash time
    static std::map<std::string, std::map<std::string, int64_t>> func_hash_time;
    static std::map<std::string, int64_t> top3;

    std::multimap<int64_t, std::string> once_time_hash;
    add_hash_func_time(func_hash_time, once_time_hash);

    if (once_time_hash.size() >= 3) {
        reset_top3(top3, once_time_hash);
    }

    const auto last  = double(once_time_hash.rbegin()->first);
    const auto first = double(once_time_hash.begin()->first);
    //print once score
    for (auto& v : once_time_hash) {
        printf("%5d   %13s   (%4.2lf %6.1lf%%)\n", int(v.first * 1000l / vsize), v.second.c_str(), last * 1.0 / v.first, first * 100.0 / v.first);
    }

    constexpr int dis_input = 10;
    if (++tcase % dis_input != 0) {
        printf("=======================================================================\n\n");
        return ;
    }

    //print function rank
    std::multimap<int64_t, std::string> score_hash;
    printf("-------------------------------- function benchmark -----------------------------------------------\n");
    dump_all(func_hash_time, score_hash);

    //print top 3 rank
    if (top3.size() >= 3)
        puts("======== hash  top1   top2  top3 =======================");
    for (auto& v : top3)
        printf("%13s %4.1lf  %4.1lf %4d\n", v.first.c_str(), v.second / (double)(base1), (v.second / (base2 / 2) % 1000) / 2.0, (int)(v.second % (base2 / 2)));

    //print hash rank
    puts("======== hash    score ================================");
    for (auto& v : score_hash)
        printf("%13s %4d\n", v.second.c_str(), (int)(v.first / func_hash_time.size()));

#if _WIN32
    Sleep(1000*2);
#else
    usleep(1000*2000);
#endif
    printf("--------------------------------------------------------------------\n\n");
}

static int benchHashMap(int n)
{
    if (n < 10000)
        n = 123456;

    check_result.clear(); once_func_hash_time.clear();

    std::vector<keyType> vList;
    auto flag = buildTestData(n, vList);

#if KEY_STR && EMH_WY_HASH
    using ehash_func = WysHasher;
#elif KEY_SUC
    using ehash_func = StuHasher;
#elif KEY_INT && BAD_HASH > 100
    using ehash_func = BadHasher<keyType>;
#elif HOOD_HASH
    using ehash_func = robin_hood::hash<keyType>;
#elif PHMAP_HASH
    using ehash_func = phmap::Hash<keyType>;
#else
    using ehash_func = std::hash<keyType>;
#endif

    {
        int64_t ts = getTime(), sum = 0ul;
        for (auto& v : vList)
#if KEY_INT
            sum += v;
#elif KEY_SUC
        sum += v.lScore;
#else
        sum += v.size();
#endif
        loop_vector_time = getTime() - ts;
        printf("%s n = %d, keyType = %s, valueType = %s(%zd), loop = %d ns:%d\n",
                __FUNCTION__, n, sKeyType, sValueType, sizeof(valueType), (int)(loop_vector_time * 1000 / vList.size()), (int)sum);
    }

    {
        func_print = func_print % func_index + 1;
#if ET > 2
        {benOneHash<tsl::hopscotch_map   <keyType, valueType, ehash_func>>("hopsco", vList); }
#if __x86_64__
        {benOneHash<ska::bytell_hash_map <keyType, valueType, ehash_func>>("byte", vList); }
#endif
#endif

#if ET > 1
        {benOneHash<emilib3::HashMap <keyType, valueType, ehash_func>>("emilib3", vList); }
        {benOneHash<std::unordered_map<keyType, valueType, ehash_func>>   ("stl_hash", vList); }
        {benOneHash<emlru_size::lru_cache <keyType, valueType, ehash_func>>("lru_size", vList); }
        {benOneHash<emlru_time::lru_cache <keyType, valueType, ehash_func>>("lru_time", vList); }

        {benOneHash<tsl::robin_map     <keyType, valueType, ehash_func>>("robin", vList); }
#if __x86_64__
        {benOneHash<ska::flat_hash_map <keyType, valueType, ehash_func>>("flat", vList); }
        {benOneHash<hrd7::hash_map     <keyType, valueType, ehash_func>>("hrdset", vList); }
#endif
#endif

#ifdef SMAP
        {benOneHash<std::map<keyType, valueType>>         ("stl_map", vList); }
#if ET
        {benOneHash<phmap::btree_map<keyType, valueType> >("btree", vList); }
#endif
#endif

#if ET
        {benOneHash<phmap::flat_hash_map <keyType, valueType, ehash_func>>("phmap", vList); }
        {benOneHash<robin_hood::unordered_flat_map <keyType, valueType, ehash_func>>("martin", vList); }
#endif

#ifdef EM3
        {benOneHash<emhash2::HashMap <keyType, valueType, ehash_func>>("emhash2", vList); }
        {benOneHash<emhash3::HashMap <keyType, valueType, ehash_func>>("emhash3", vList); }
        {benOneHash<emhash4::HashMap <keyType, valueType, ehash_func>>("emhash4", vList); }
#endif
        {benOneHash<emhash5::HashMap <keyType, valueType, ehash_func>>("emhash5", vList); }
        {benOneHash<emhash6::HashMap <keyType, valueType, ehash_func>>("emhash6", vList); }
        {benOneHash<emhash7::HashMap <keyType, valueType, ehash_func>>("emhash7", vList); }
    }

    auto pow2 = 1 << ilog(vList.size(), 2);
    auto iload = 50 * vList.size() / pow2;
    printf("\n %d ======== n = %d, load_factor = %.2lf, data_type = %d ========\n", tcase + 1, n, iload / 100.0, flag);
    printResult(n);
    return tcase;
}

#ifdef TREAD
static int readFile(std::string fileName, int size)
{
    if (!freopen(fileName.c_str(), "rb", stdin)) {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        freopen(CONSOLE, "r", stdin);
        return -1;
    }

    auto ts1 = getTime();
    std::vector<int64_t> vList;
    vList.reserve(1038860);

    int64_t                uid, score, pid;
    if (size == 1) {
        while (scanf("%ld", &uid) == size) vList.emplace_back(uid);
    } else if (size == 2) {
        while (scanf("%ld %ld", &uid, &score) == size) vList.emplace_back(uid);
    } else if (size == 6) {
        int items = 0;
        while (scanf("%ld %ld %d %ld %d %d", &uid, &pid, &items, &score, &items, &items) == size)
            vList.emplace_back(pid + uid + score + items);
    }
    freopen(CONSOLE, "r", stdin);

    //    std::sort(vList.begin(), vList.end());
    int n = (int)vList.size();
    printf("\nread file %s  %ld ms, size = %zd\n", fileName.c_str(), (getTime() - ts1) / 1000, vList.size());

#if HOOD_HASH
    using hash_func = robin_hood::hash<int64_t>;
#else
    using hash_func = std::hash<int64_t>;
#endif
    n = 25 * 10000 * 2;

    emhash2::HashMap<int64_t, int, hash_func> ehash2(n);
    emhash6::HashMap<int64_t, int, hash_func> ehash6(n);
    emhash7::HashMap<int64_t, int, hash_func> ehash7(n);
    emhash5::HashMap<int64_t, int, hash_func> ehash5(n);

#if _CPP11_HASH
    ska::flat_hash_map <int64_t, int, hash_func> fmap(n); fmap.max_load_factor(7.0/8);
    //tsl::robin_map     <int64_t, int, hash_func> rmap(n); rmap.max_load_factor(7.0/8);
    hrd7::hash_map     <int64_t, int, hash_func> hmap(n); hmap.max_load_factor(7.0/8);
    phmap::flat_hash_map<int64_t, int> pmap(n);
    robin_hood::unordered_map<int64_t, int> mmap(n);
    emilib3::HashMap   <int64_t, int, hash_func> emap(n);
#endif

    ts1 = getTime();    for (auto v : vList)        ehash6[v] = 1; printf("emhash6   insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, ehash6.size(), ehash6.load_factor());
    ts1 = getTime();    for (auto v : vList)        ehash2[v] = 1; printf("emhash2   insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, ehash2.size(), ehash2.load_factor());

#if _CPP11_HASH
    ts1 = getTime();    for (auto v : vList)        fmap[v] = 1;   printf("ska       insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, fmap.size(), fmap.load_factor());
    //ts1 = getTime();    for (auto v : vList)        rmap[v] = 1;   printf("tsl       insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, rmap.size(), rmap.load_factor());
    ts1 = getTime();    for (auto v : vList)        pmap[v] = 1;   printf("pmap      insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, pmap.size(), pmap.load_factor());
    ts1 = getTime();    for (auto v : vList)        mmap[v] = 1;   printf("martin    insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, mmap.size(), mmap.load_factor());
    ts1 = getTime();    for (auto v : vList)        emap[v] = 1;   printf("emilib3   insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, emap.size(), emap.load_factor());
    ts1 = getTime();    for (auto v : vList)        hmap[v] = 1;   printf("hrd7      insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, hmap.size(), hmap.load_factor());
#endif
    ts1 = getTime();    for (auto v : vList)        ehash7[v] = 1; printf("emhash7   insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, ehash7.size(), ehash7.load_factor());
    ts1 = getTime();    for (auto v : vList)        ehash5[v] = 1; printf("emhash5   insert  %6ld ms, size = %zd|%.2f\n", getTime() - ts1, ehash5.size(), ehash5.load_factor());

    printf("\n");
    return 0;
}
#endif

static void cpuidInfo(int regs[4], int id, int ext)
{
#if __x86_64__ || _M_X64 || _M_IX86 || __i386__
#if _MSC_VER >= 1600 //2010
    __cpuidex(regs, id, ext);
#elif __GNUC__ || __TINYC__
    __asm__ (
            "cpuid\n"
            : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3])
            : "a"(id), "c"(ext)
            );
#elif ASM_X86
    __asm
    {
        mov eax, id
            mov ecx, ext
            cpuid
            mov edi, regs
            mov dword ptr [edi + 0], eax
            mov dword ptr [edi + 4], ebx
            mov dword ptr [edi + 8], ecx
            mov dword ptr [edi +12], edx
    }
#endif
#endif
}

static void printInfo(char* out)
{
    const char* sepator =
        "------------------------------------------------------------------------------------------------------------";

    puts(sepator);
    //    puts("Copyright (C) by 2019-2020 Huang Yuanbing bailuzhou at 163.com\n");

    char cbuff[512] = {0};
    char* info = cbuff;
#ifdef __clang__
    info += sprintf(info, "clang %s", __clang_version__); //vc/gcc/llvm
#if __llvm__
    info += sprintf(info, " on llvm/");
#endif
#endif

#if _MSC_VER
    info += sprintf(info, "ms vc++  %d", _MSC_VER);
#elif __GNUC__
    info += sprintf(info, "gcc %d.%d.%d", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif __INTEL_COMPILER
    info += sprintf(info, "intel c++ %d", __INTEL_COMPILER);
#endif

#if __cplusplus > 199711L
    info += sprintf(info, " __cplusplus = %d", static_cast<int>(__cplusplus));
#endif

#if __x86_64__ || __amd64__ || _M_X64
    info += sprintf(info, " x86-64");
#elif __i386__ || _M_IX86
    info += sprintf(info, " x86");
#elif __arm64__ || __aarch64__
    info += sprintf(info, " arm64");
#elif __arm__
    info += sprintf(info, " arm");
#else
    info += sprintf(info, " unknow");
#endif

#if _WIN32
    info += sprintf(info, " OS = Win");
    SetThreadAffinityMask(GetCurrentThread(), 0x1);
#elif __linux__
    info += sprintf(info, " OS = linux");
#elif __MAC__
    info += sprintf(info, " OS = MAC");
#elif __unix__
    info += sprintf(info, " OS = unix");
#else
    info += sprintf(info, " OS = unknow");
#endif

    info += sprintf(info, ", cpu = ");
    char vendor[0x40] = {0};
    int (*pTmp)[4] = (int(*)[4])vendor;
    cpuidInfo(*pTmp ++, 0x80000002, 0);
    cpuidInfo(*pTmp ++, 0x80000003, 0);
    cpuidInfo(*pTmp ++, 0x80000004, 0);

    info += sprintf(info, vendor);

    puts(cbuff);
    if (out)
        strcpy(out, cbuff);
    puts(sepator);
}

#if WYHASH_LITTLE_ENDIAN && STR_VIEW
struct string_hash
{
    using is_transparent = void;

    std::size_t operator()(const std::string& key)    const { return wyhash(key.c_str(), key.size(), 11400714819323198485ull); }
    std::size_t operator()(const std::string_view& key)    const { return wyhash(key.data(), key.size(), 11400714819323198485ull); }
    std::size_t operator()(const char* key)        const { return wyhash(key, std::strlen(key), 11400714819323198485ull); }
};

struct string_equal
{
    using is_transparent = int;

 //   bool operator()(const std::string_view& lhs, const std::string& rhs) const {
//        return lhs.size() == rhs.size() &&
//            (lhs.data() == rhs.data() || std::strcmp(lhs.data(), rhs.data()) == 0);
//    }

    bool operator()(const std::string& rhs, const std::string_view& lhs) const {
        return lhs.size() == rhs.size() &&
            (lhs.data() == rhs.data() || std::strcmp(lhs.data(), rhs.data()) == 0);
    }

//    bool operator()(const char* lhs, const std::string& rhs) const { return std::strcmp(lhs, rhs.c_str()) == 0; }
    bool operator()(const std::string& rhs, const char* lhs) const { return std::strcmp(lhs, rhs.c_str()) == 0; }
};

int find_test()
{
    emhash6::HashMap<std::string, uint64_t, string_hash, string_equal> map;
    std::string_view key = "key";
    map.emplace(key, 100);
    const auto it = map.find(key); // fail
    assert(it == map.find("key"));
    assert(it == map.find(std::string("key")));

    assert(key == "key");
    assert(key == std::string("key"));
    return 0;
}
#endif

int main(int argc, char* argv[])
{
#if HOOD_HASH && STR_VIEW
    find_test();
#endif

    srand((unsigned)time(0));

    printInfo(nullptr);

    bool auto_set = false;
    int tn = 0, rnd = time(0) + rand() * rand();
    auto maxc = 500;
    auto maxn = (1024 * 1024 * 64) / (sizeof(keyType) + sizeof(valueType) + 8) + 100000;
    auto minn = (1024 * 1024 * 2) /  (sizeof(keyType) + sizeof(valueType) + 8) + 10000;

    float load_factor = 0.0945;
    printf("./ebench maxn = %d i[0-1] c(0-1000) f(0-100) d[2-9 h m p s f u e l] t(n)\n", (int)maxn);

    for (int i = 1; i < argc; i++) {
        const auto cmd = argv[i][0];
        if (isdigit(cmd))
            maxn = atoi(argv[i]) + 1000;
        else if (cmd == 'f' && isdigit(argv[i][1]))
            load_factor = atof(&argv[i][0] + 1) / 100.0f;
        else if (cmd == 't' && isdigit(argv[i][1]))
            tn = atoi(&argv[i][0] + 1);
        else if (cmd == 'c' && isdigit(argv[i][1]))
            maxc = atoi(&argv[i][0] + 1);
        else if (cmd == 'i' && isdigit(argv[i][1]))
            auto_set = atoi(&argv[i][0] + 1) != 0;
        else if (cmd == 'r' && isdigit(argv[i][1]))
            rnd = atoi(&argv[i][0] + 1);

        else if (cmd == 'd') {
            for (char c = argv[i][1], j = 1; c != '\0'; c = argv[i][++j]) {
                if (c >= '2' && c <= '9') {
                    std::string hash_name("emhash");
                    hash_name += c;
                    if (hash_tables.find(hash_name) != hash_tables.end())
                        hash_tables.erase(hash_name);
                    else
                        hash_tables[hash_name] = hash_name;
                }
                else if (c == 'h')
                    hash_tables.erase("hrdset");
                else if (c == 'm')
                    hash_tables.erase("martin");
                else if (c == 'p')
                    hash_tables.erase("phmap");
                else if (c == 't')
                    hash_tables.erase("robin");
                else if (c == 's')
                    hash_tables.erase("flat");
                else if (c == 'e') {
                    hash_tables.insert("emilib2", "emilib2");
                    hash_tables.insert("emilib3", "emilib3");
                    hash_tables.insert("emilib4", "emilib4");
                } else if (c == 'l') {
                    hash_tables.insert("lru_size", "lru_size");
                    hash_tables.insert("lru_time", "lru_time");
                }
                else if (c == 'k')
                    hash_tables.insert("ktprime", "ktprime");
                else if (c == 'b') {
                    hash_tables.insert("btree", "btree_map");
                    hash_tables.insert("smap", "stl_map");
                } else if (c == 'u')
                    hash_tables.insert("stl_hash", "unordered_map");
            }
        }
    }

#ifndef KEY_SUC
    if (tn > 100000)
        TestHashMap(tn);
#endif

#ifdef TREAD
    //readFile("./uid_income.txt", 1);
    //readFile("./pid_income.txt", 1);
    //readFile("./uids.csv", 2);
    readFile("./item.log", 6);
#endif

    sfc64 srng(rnd);
    for (auto& m : hash_tables) {
        printf("  %s\n", m.second.data());
    }

    while (true) {
        int n = (srng() % maxn) + minn;
        if (auto_set) {
            printf(">> "); scanf("%u", &n);
            if (n <= 0)
                auto_set = false;
        }
        if (load_factor > 0.2 && load_factor < 1) {
            auto pow2 = 1 << ilog(n, 2);
            n = int(pow2 * load_factor) - (1 << 10) + (srng()) % (1 << 8);
        }
        if (n < 1000 || n > 1234567890)
            n = 1234567;

        int tc = benchHashMap(n);
        if (tc >= maxc)
            break;
    }

    return 0;
}

