# httplib

## 响应头部

**HTTP 响应头部** 是服务器在响应客户端的 HTTP 请求时发送的一系列头字段，它们提供了关于响应的附加信息和服务器的指令。

- **Date**：响应生成的日期和时间。
- **Server**：服务器软件的名称和版本。
- **Content-Type**：响应体的媒体类型（MIME 类型），如 `text/html; charset=UTF-8`, `application/json` 等。
- **Content-Length**：响应体的大小，单位是字节。
- **Content-Encoding**：响应体的压缩编码，如 `gzip`, `deflate` 等。
- **Content-Language**：响应体的语言。
- **Cache-Control**：控制响应的缓存行为, 如 `no-cache` 表示必须重新请求。
- **Set-Cookie**：设置客户端的 cookie。
- **Allow**：列出资源允许的 HTTP 方法，例如 `GET`, `POST`，`HEAD` 等。

<br>

## HTTP 请求方法

- 大部分方法都只传入俩个参数：

  - `path`：请求的路径。
  - `handler`：处理函数，这个函数接收一个 `Request` 对象和一个 `Response` 对象。

  ```cpp
  svr.Get(path, handler);
  ```

- 同一个 api 地址可设置多个 HTTP 请求

<br>

## Request, Response 对象

**req** 请求对象, **res** 响应对象

**Request 对象**：

- **method**：请求方法，如 "GET"、"POST" 等。
- **path**：请求的路径。
- **headers**：请求头，是一个字典，包含了所有的 HTTP 头部信息。
- **body**：请求体，包含了发送给服务器的数据。

**Response 对象**：

- **status**：响应的状态码，如 200、404 等。
- **headers**：响应头，是一个字典，包含了所有的 HTTP 头部信息。
- **body**：响应体，包含了服务器返回的数据。

<br>

## set_header()

设置 HTTP 响应的头部信息

- **Content-Type**：指定响应体的媒体类型
- **Access-Control-Allow-Origin**：设置跨源资源共享，指定哪些源可以访问资源。设置`URL`特定的源设置跨域请求，设置`*`允许特定的源进行跨域请求
- **Access-Control-Allow-Methods**：指定哪些 HTTP 方法可以用于访问资源。例如 `GET`，`POST`，`PUT`，`DELETE` 等。
- _（以下的具体用法尚不明确）_
- **Access-Control-Allow-Headers**: 指定哪些 HTTP 头部可以用于实际的请求。
- **Access-Control-Max-Age**: 指定预检请求的结果可以被缓存多久。
- **Set-Cookie**: 设置 Cookie。
- **Cache-Control**: 控制缓存行为。
- **Expires**: 指定资源的过期时间。

<br>

### set_default_headers()

这个函数用于设置默认的 HTTP 头部，这些头部将应用于所有的响应 。

例：

```cpp
svr.set_default_headers({
  { "Access-Control-Allow-Origin", "*" },
  { "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS" },
  { "Access-Control-Allow-Headers", "Content-Type" }
});
```

## set_content()

在 C++ 的 `httplib` 库中，`set_content` 方法用于设置 HTTP 响应的主体内容。

1. **设置文本内容**：

例：

```cpp
res.set_content("Hello, World!", "text/plain");
```

2. **设置 JSON 内容**：

例：

```cpp
res.set_content("{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}", "application/json");
```

安装 `nlohmann/json.hpp` 库的情况下：

```cpp
using json = nlohmann::json;

httplib::Server svr;

svr.Get("/api", {
json j;
j["name"] = "John";
j["age"] = 30;
j["city"] = "New York";

res.set_content(j.dump(), "application/json");
});
```

3. **设置二进制内容**：

例如，你可以这样设置一个图片文件：

```cpp
ifstream file("image.jpg", ios::binary);
vector<char> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
res.set_content(std::string(data.begin(), data.end()), "image/jpeg");
```

<br>

### Content-Type 内容类型

- **文本（Text）**：

  - `text/html`：HTML 格式
  - `text/plain`：纯文本格式
  - `text/xml`：XML 格式
  - `text/css`：CSS 格式
  - `text/javascript`：JavaScript 格式

- **图像（Image）**：

  - `image/gif`：GIF 图片格式
  - `image/jpeg`：JPEG 图片格式
  - `image/png`：PNG 图片格式
  - `image/webp`：WebP 图片格式

- **音频（Audio）**：

  - `audio/mpeg`：MP3 音频格式
  - `audio/ogg`：OGG 音频格式
  - `audio/*`：所有音频格式

- **视频（Video）**：

  - `video/mp4`：MP4 视频格式
  - `video/webm`：WebM 视频格式

- **应用（Application）**：
  - `application/octet-stream`：二进制流数据（如常见的文件下载）
  - `application/json`：JSON 数据格式
  - `application/xml`：XML 数据格式
  - `application/pdf`：PDF 格式
  - `application/zip`：ZIP 压缩文件格式

<br>

# axios

## HTTP 请求方法

_实际上感觉这么多请求只用一个 **post** 就行了_

- **get**：用于获取数据，请求指定的信息，返回实体对象，是安全的和幂等的，这意味着它不应该改变服务器上的状态。

  - `url`：要发送请求的 URL。
  - `config`：请求的配置选项，这是一个可选参数。

  ```javascript
  axios.get(url, config)
  ```

- **post**：用于向后端提交数据。

  - `url`：要发送请求的 URL。
  - `data`：要发送的数据，可以是对象、数组、字符串等。
  - `config`：请求的配置选项，这是一个可选参数。

  ```javascript
  axios.post(url, data, config)
  ```

- **put**：用于更新数据，从客户端向服务器传送的数据取代指定的文档的内容。

  - `url`：要发送请求的 URL。
  - `data`：要发送的数据，可以是对象、数组、字符串等。
  - `config`：请求的配置选项，这是一个可选参数。

  ```javascript
  axios.put(url, data, config)
  ```

- **patch**：用于更新数据，只将修改的数据推送到后端。

  - `url`：要发送请求的 URL。
  - `data`：要发送的数据，可以是对象、数组、字符串等。
  - `config`：请求的配置选项，这是一个可选参数。

  ```javascript
  axios.patch(url, data, config)
  ```

- **delete**：用于删除数据。

  - `url`：要发送请求的 URL。
  - `config`：请求的配置选项，这是一个可选参数。

  ```javascript
  axios.delete(url, config)
  ```

<br>

## response 对象

- **data**：服务器返回的数据。
- **status**：来自服务器响应的 HTTP 状态码。
- **statusText**：来自服务器响应的 HTTP 状态信息 。
- **headers**：服务器的响应头。所有的 header 名称都是小写，可以使用方括号语法访问，例如：`response.headers['content-type']`。
- **config**：`axios` 请求的配置信息。
- **request**：生成此响应的请求。在 node.js 中，它是最后一个 `ClientRequest` 实例，在浏览器中则是 `XMLHttpRequest` 实例。
