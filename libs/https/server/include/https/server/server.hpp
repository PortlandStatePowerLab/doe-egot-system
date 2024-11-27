#ifndef __HTTPS_SERVER_H__
#define __HTTPS_SERVER_H__
//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <flecs.h>
#include <memory>
#include <string>

class HttpsServer {
public:
  HttpsServer(const std::string &address, uint16_t port,
              const std::string &doc_root, int threads);
  ~HttpsServer();

private:
  bool stop;
  std::string address_;
  uint16_t port_;
  std::shared_ptr<std::string> doc_root_;
};

#endif // __HTTPS_SERVER_H__
