# A - Restaurant Order
## 任務
- Input: n 個餐點的價格和 m 個 order 的總價
- Output: 輸出 m 個答案，
    - 如果價格可以用餐點的價錢湊不出來，輸出 `Impossible`，
    - 若有多於一種餐點的組合可以湊出這個價格，輸出 `Ambiguous`，
    - 若剛好只有一種組合可以湊出這個價格，以升序輸出該組合的餐點 index (e.g. 若只可以用兩個餐點 1 號和一個餐點 3 號湊成，輸出: `1 1 3`)

## 分析
背包問題的衍伸。湊錢問題。直覺用 dp。

### dp 陣列定義
`dp[j]`: 總價 = j 時，的這個問題的答案。
- `dp[j]`=0, if 湊不出總價 j
- `dp[j]`=-1, if 有多種湊法
- `dp[j]`=idx, if 有唯一湊法, 且這個湊法用到商品 idx 號

`p[i]`: 商品 i 的價格

1. 在 `p[i]` 倍數處有解
2. 在"有解處+`p[i]` 倍數處"有解
3. 若判斷 `dp[x]` 有解，但 `dp[x]` 已經存有解，設 `dp[x]=-1` 
4. 若 `p[i]` 本身有多種解，則對所有已經有解的 `dp[i]`， `dp[i+p[i]]` 也有多種解。

# Reference
- Ref sol: https://vjudge.net/solution/snapshot/36510231
- Money Changing Problem: https://web.ntnu.edu.tw/~algo/KnapsackProblem.html
