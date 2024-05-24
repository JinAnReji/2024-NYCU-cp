# B-Presidential Elections
問題連結: https://vjudge.net/problem/Kattis-presidentialelections

## 要解的問題
似乎是 min-Knapsack problem。

1. n 個浮動 state，各有各自的代表數和需要說服的 voter 數。還差 m 張代表票來贏，求需要說服的最少 voter 總數。
    - 轉譯問題: 最少要湊到 m 元，有 n 種物品，每一種物品值 d_i 元，以湊到為前提，想要使物品的權重(aka 需要說服的人數)總和最小，求該最小權重和。
        - 暴力解: 算出所有湊得到 m 元的組合，計算出其中權重和最小者
            - 窮舉所有湊得到 m 元的組合，需要付出的代價: ? 
        - dp 解: 
            - 求: 每個物品有重量(需要說服的投票人數)和價值(代表人票數)，在湊滿(可以超過，不一定要剛好)給定價值 m 的前提下，重量最小的物品總重。
            - sketch1: 
                - 令 dp[p]= 湊得到 p 元的組合的最小權重和
                - dp[p] = dp[p-1] + ?
            - sketch2: 
                - idea: 這類似於"背包裡面的物品盡量最少（多）個" 的 0/1 背包問題?
                - dp[0,p] = -INF --> 
                - dp[n,0] = 0  --> 湊出至少價值 0 的最小重量是 0 
                - dp[n,p] = 考慮 1~n 個不同物品，能湊出 p 元的最小權重和
                - dp[n,p] = min( dp[n-1,p], dp[n-1, p-d[n] ]+w[n]   )
                - `w[n]`: 物品 n 的權重 
2. 對每個浮動 state，計算出還需要說服的最少人數來讓該州傾向 C 黨 (s.t. 它的代表人票會全都投給 C 黨)。
    - 計算方式: (f+c+u)/2+1 - c 
3. 對每個 state，計算那些是浮動 state，哪些是確定投 F 黨(簡稱確F)，哪些是確定投 C 黨(簡稱確 C)。
    - 確 F: f >= c+u
    - 確 C: c > f+u
    - 浮動: o.w. (2.)
4. 有無勝算的判斷: 若確 F 代表票數 >= 確 C 代表票數 + 所有浮動州的票數，則確定無勝算。否則就還有勝算。
5. 若有勝算，計算最少需要說服多少人。(= 1 的答案的 sum )
6. 還至少差 m 張代表票來贏。計算 m =(n_c+n_f+n_u)/2+1-n_c


問題的相依性:
- 3,2 --> 1 --> 5
- 3,2 --> 4 
- 3,2 --> 5

## 資料結構
- `u_state`: 儲存所有浮動州的 index 和 需要說服的人數 w 的 pair。


### 空間複雜度
O(WN): W 價值， N 物品數量
- 2D array size 最大會用到: 2016 * 1e9 = 2.016e13 < 1e14 
    - 8 bytes * 1e14 = 8 * 1e11 kb 
    - 用 2D array 的話超出容量限制而造成 runtime error 也不奇怪，必須再縮減
- limitation: 1048576 kB

嘗試空間複雜度 O(W) 的寫法: (一樣參考 [解說 knapsack problem 的 blog](https://web.ntnu.edu.tw/~algo/KnapsackProblem.html) )
- 改成長度 m 的 1D array，從右端填回左端，陣列初始值設 INF
- dp[m]: 要湊滿至少價值 m 所需要的最少重量
- 初始化: INF 或 物品重量總和
- p[n]: 物品 n 的價值
- w[n]: 物品 n 的重量
- 程式 sketch
```cpp
for(int n=0; n<N; n++)
// 對每一個物品，都從尾到頭掃過陣列 dp[M] 一次
    for(int m=M; m>0; m--)
        // 如果替換成物品 n 會比較輕，且滿足至少要有價值 m 在背包裡的條件，則更新
        if (is_valid_to_put_n)
        dp[m] = min(dp[m],  
                    dp[m-p[n]]+w[n]) 
```
- 問題: 有可能對每個物品，單一放都滿足不了最小價值條件，要組合才可以
    - 用 "所有物品都放" 來初始化?
        - 初始狀態下，所有物品都選，dp[m]= total w[n]
        - 對每個物品，去檢查 "拿掉物品 n ，是不是仍符合要求"，若通過，就拿掉 (減去 w[n])，否則就不拿掉
        - 因為對每個 dp[m] 都會檢查 N 個物品是不是可以拿掉，所以也符合時間複雜度 O(NM) (但空間複雜度就變成 O(M))
        - 衍伸問題: dp[m-p[n]] - w[n] 的 m-p[n] 項的意義變得模糊 。先不論 m-p[n] 可能是負的，就算不是，這也不直接 implies dp[m] 的答案就會是此值和 dp[m] 之間取最小。(dp[m]: 符合最低價值要求 >= m 的重量)

再觀察一次 0/1 knapsack 問題的 1D array 解法: (參考同一個 blog)
```cpp
const int N = 100, W = 100000;
// 物品的價值與重量，合併成一個物件，讓人容易理解。
struct Item {int cost, weight;} items[N];
int c[W + 1];

void knapsack(int n, int w)
{
	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; ++i)
	{
		int weight = items[i].weight;
		int cost = items[i].cost;
		for (int j = w; j - weight >= 0; --j)
			c[j] = max(c[j], c[j - weight] + cost);
	}

	cout << "最高的價值為" << c[w];
}
```
- 上面這個一維陣列版本的解之所以正確，因為
    - c[j]: 能用 capacity j 裝下的最大價值
    - 遞迴式 c[j] = max(c[j], c[j - weight] +cost) 成立
- 反觀我現在試圖寫的版本:
    - 遞迴式 dp[m] = min(dp[m], dp[m - p[n]] + w[n]) 成立? 不成立?
    - 一個問題是 dp[m] 的定義是: 滿足價值**大於等於** m 的最小重量
    - 這個大於等於的存在把一切秩序都打亂了。
    - 假如今天知道 dp[j] 的解好了，也就是說我知道滿足價值大於等於 j 的最小重量，那問題是這會有助於我解答 dp[j + p[n]] 時的答案嗎?
        - 換句話說，我會因為知道要湊到 j 至少需要多少重量，就進而能推得要湊到 j+p[n] 時需要的最小重量嗎? 這件事沒有想像中的那麼直觀。
        - 如果物品 1,2,3 的組合是 dp[j] 這麼重，那 dp[j+p[4]] 就保證是物品 1+2+3+4 的重量嗎?
            - 不一定。假如今天 dp[j].price = 10，j=9，而 p[4]=1 的話，那就其實不用新增任何物品才是正解。
            - 在這個 case，dp[j+p[4]] = dp[j].price >= j+p[4] ? dp[j] : dp[j]+w[4]; 
            - 這個觀察下有另一個發現是，dp 的陣列大小應設為物品的總價，而不是目標總價。
            - 假如這個遞迴式正確，下一個問題是，該從哪個方向去更新 dp[M]? 由右向左或由左向右?
            - 假設初期值設所有物品都選
                - 由左向右: 一個一個去 test 拿掉 n 之後 dp[j] 是否可以更新 (j = M~p[n])
                    - 遞迴式: 
                        - base case: dp[0] = {0,0} ?
                        - general case: dp[j].weight = dp[j].price-p[n] >= j ? min(dp[j].weight, dp[j-p[n]].weight - w[n]) : dp[j].weight ;
```cpp
for(int n=1; n<=N; n++)
    for(int j=0; j<M; j++)
        dp[j].weight = dp[j].price-p[n] >= j ?dp[j].weight-w[n] : dp[j].weight ;
```
