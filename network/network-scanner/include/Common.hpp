#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef ssize_t usize;

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <future>
#include <functional>

using std::map;
using std::string;
using std::vector;
using std::cerr;
using std::endl;
using std::cout;
using std::future;
using std::async;
using std::mutex;
using std::unique_ptr;

#define self (*this)
#define fn auto

#include "Const.hpp"

#endif __COMMON_H__