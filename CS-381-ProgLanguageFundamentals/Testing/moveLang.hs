data Dir  = N | S | E | W
data Step = Go Dir Int
type Move = [Step]

type Pos = (Int, Int)

step :: Step -> Pos -> Pos
step (Go N k) (x,y) = (x,y+k)
step (Go S k) (x,y) = (x,y-k)
step (Go E k) (x,y) =  (x+k,y)
step (Go W k) (x,y) = (x-k,y)
