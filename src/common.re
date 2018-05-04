type gridCell =
  | X
  | O
  | Empty;

let gridCellToString = gc =>
  switch (gc) {
  | X => "X"
  | O => "O"
  | Empty => "No one"
  };

type t('a) =
  | ClientConnect: t(unit)
  | Message: t('a)
  | Move: t(int)
  | ServerConnect: t(gridCell)
  | InitRestart: t(unit)
  | RolloutRestart: t(unit);

let stringify = (type a, t: t(a)) =>
  switch (t) {
  | ClientConnect => "ClientConnect"
  | Message => "Message"
  | Move => "Move"
  | ServerConnect => "SeverConnect"
  | InitRestart => "InitRestart"
  | RolloutRestart => "RolloutRestart"
  };