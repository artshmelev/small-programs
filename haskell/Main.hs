prty :: String -> Int
prty "+" = 1
prty "-" = 2
prty "*" = 3
prty "/" = 3
prty _ = -1
 
lexType :: String -> Int
lexType x | (x `elem` ["+", "-", "*", "/"]) = 1
          | (x `elem` ["(", ")"]) = 2
          | otherwise = 0

parse :: String -> String -> [String] -> [String]
parse [] lex r = r ++ [lex]
parse (x:xs) lex r | ((lexType [x]) == 1 || (lexType [x]) == 2) =
                       if (length lex) > 0 then parse xs [] (r ++ [lex] ++ [[x]]) else parse xs [] (r ++ [[x]])
                   | otherwise = (parse xs (lex ++ [x]) r)

convert :: [String] -> [String] -> [String] -> [String]
convert [] inp [] = inp
convert [] inp (sth:st) = convert [] (inp ++ [sth]) st
convert (x:xs) inp [] | (lexType x) == 0 = convert xs (inp ++ [x]) []
                      | otherwise        = convert xs inp [x]
convert (x:xs) inp (sth:st) | (lexType x) == 0                           = convert xs (inp ++ [x]) (sth:st)
                            | (lexType x) == 1 && (prty x) <= (prty sth) = convert (x:xs) (inp ++ [sth]) st
                            | (lexType x) == 1                           = convert xs inp (x:sth:st)
                            | x == "("                                   = convert xs inp (x:sth:st)
                            | x == ")" && sth /= "("                     = convert (x:xs) (inp ++ [sth]) st
                            | x == ")"                                   = convert xs inp st

strip :: [String] -> [String]
strip [] = []
strip (x:xs) = if (x == []) then strip xs else x : strip xs

-- RPN output
convertString :: String -> [String]
convertString x = convert (strip (parse x [] [])) [] []

calc :: [String] -> Float
calc x = head (foldl f [] x) 
         where f :: [Float] -> String -> [Float]
               f (x:y:zs) "+" = (y + x):zs
               f (x:y:zs) "-" = (y - x):zs
               f (x:y:zs) "*" = (y * x):zs
               f (x:y:zs) "/" = (y / x):zs
               f xs y         = read y :xs

-- Calc output
calcExpr :: String -> Float
calcExpr x = calc (convertString x)

data Tree = Empty | Node Tree String Tree --deriving (Show)
buildTree :: [String] -> [Tree] -> Tree
buildTree [] ts = head ts
buildTree (x:xs) [] = buildTree xs [Node Empty x Empty]
buildTree (x:xs) [t1] = buildTree xs ([Node Empty x Empty]++[t1])
buildTree (x:xs) (t1:t2:ts) | lexType(x) == 0 = buildTree xs ((Node Empty x Empty):t1:t2:ts)
                            | otherwise = buildTree xs ((Node t2 x t1):ts)
                            
--
instance Show Tree where
  show t = "< " ++ replace '\n' "\n: " (treeshow "" t)
    where
    treeshow pref Empty = ""
    treeshow pref (Node Empty x Empty) =
                  (pshow pref x)
    treeshow pref (Node left x Empty) =
                  (pshow pref x) ++ "\n" ++
                  (showSon pref "`--" "   " left)
    treeshow pref (Node Empty x right) =
                  (pshow pref x) ++ "\n" ++
                  (showSon pref "`--" "   " right)
    treeshow pref (Node left x right) =
                  (pshow pref x) ++ "\n" ++
                  (showSon pref "|--" "|  " left) ++ "\n" ++
                  (showSon pref "`--" "   " right)
    showSon pref before next t =
                  pref ++ before ++ treeshow (pref ++ next) t
    pshow pref x = replace '\n' ("\n"++pref) (show x)
    replace c new string =
      concatMap (change c new) string
      where
          change c new x
              | x == c = new
              | otherwise = x:[]
--
-- Tree Output
getTree :: String -> Tree
getTree x = buildTree (convertString x) []

