# midware-ice-service

ICE异步SERVER，并集成libgo携程库，实现中间件服务（示例，具体的服务逻辑需要DIY）

安装约定:

依赖的CPP库统一安装在目录: /home/apps/cpplibs/下，如：
  boost-1.61安装目录: /home/apps/cpplibs/boost-1.61.0
  libgo安装目录: /home/apps/cpplibs/libgo (master)

接口约定:
  interface Srv {
      ["amd"] idempotent bool Call(string rqstid, string method, string rqst, out string resp);
  };

  amd: Asynchronous Method Dispatch(AMD)，标明接口SERVER端使用异步ICE机制实现。
  idempotent: 因为ICE是基于At-Most-Once Semantics。An idempotent operation is an operation that, if executed twice, has the same effect as if executed once. 即idempotent表示接口可重入，根据业务情况添加或去除。

  函数原型:
    bool Call(string rqstid, string method, string rqst, out string resp);
    参数:
      rqstid: 可以唯一跟踪服务调用情况
      method: 调用方法名，可以区分不同的操作
      rqst: 请求参数，推荐使用json格式（示例使用json）
      resp: 输出参数，返回结果，推荐使用json格式（后续引入聚合中间件要求符合一定格式）

运行:
  1. 参照'midware-ice-cluster'搭建基本的ICE集群（也可以是单机环境）
  2. 编译生成midware-ice-service和midware-ice-service-client
  3. 与config下文件部署在同一目录
  4. sh ctrl.sh查看操作说明
     第一次部署需要: sh ctrl.sh add 
     application.xml存在更新时: sh ctrl.sh update
     启动服务: sh ctrl.sh start
     停止服务: sh ctrl.sh stop
     升级服务: sh ctrl.sh stop_disable  ## 应为ICE框架当请求到来时会自动调起服务，所以必须先disable后，再更新binary程序；因为在程序运行时更新binary会失败，无法完成升级，所以需要stop and disable。
     升级完成: sh ctrl.sh start_enable  ## 升级完后，通过start_enable启动服务


欢迎交流QQ群: 92799001


