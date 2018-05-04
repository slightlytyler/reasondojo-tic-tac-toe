module Server = BsSocket.Server.Make(Common);

let startSocketIOServer = http => {
  print_endline("starting socket server");
  let io = Server.createWithHttp(http);
  let isFirst = ref(true);
  Server.onConnect(
    io,
    socket => {
      Server.Socket.on(
        socket,
        Common.ClientConnect,
        () => {
          let player = isFirst^ ? Common.X : Common.O;
          Server.Socket.emit(socket, Common.ServerConnect, player);
          isFirst := false;
        },
      );
      Server.Socket.on(
        socket,
        Common.Move,
        pos => {
          Server.Socket.emit(socket, Common.Move, pos);
          Server.Socket.broadcast(socket, Common.Move, pos);
        },
      );
      Server.Socket.on(
        socket,
        Common.InitRestart,
        () => {
          Server.Socket.emit(socket, Common.RolloutRestart, ());
          Server.Socket.broadcast(socket, Common.RolloutRestart, ());
        },
      );
    },
  );
};