# LCS
longest common sequence for PNU Computer Algorithm

1.	함수 정의
(1)	Int checkScore(int i, int j, string DNA1, string DNA2, int** score, int** gaparr)
-	정의: DNA1의 i번째 문자와 DNA2의 j번째 문자를 비교하여 점수를 매긴다.
-	입력: i = DNA1에서 비교할 위치, j = DNA2에서 비교할 위치, DNA1, DNA2 = 비교할 두 DNA sequence, score = score를 저장할 행렬, gaparr = 해당 행렬의 score가 어느 값에서 파생된건지 표시하는 행렬
-	출력: 현재 행렬의 스코어의 파생 위치

(2)	Int max(int I, int j, int k, int* gap)
-	정의: 3값을 비교하여 최대 값을 찾고, 그 값이 몇 번째 값인지 gap에 저장해라
-	입력: I,j,k = 비교할 3개의 정수, gap 어떤 매개변수가 가장 큰지를 저장할 공간
-	출력: 3개의 수 중 가장 큰 값

(3)	void isTop5(int num, int** top5, int I, int j)
-	정의: 입력 받은 score가 top5에 저장된 score중 하나보다 크다면 top5에 그 수 대신 저장하라
-	입력: num = 비교할 점수, top5 = 현재 가장 높은 점수를 받은 상위 5개 문자의 점수와 위치, I, j = 현재 비교할 점수의 위치
-	출력: 없음 
(4)	String LCS_i(int I, int j, int **score, int ** gap, string dna, int *end. Int *start)
-	정의: DNA서열정렬방법과 현재 score를 활용하여 DNA1와 DNA2의 LCS를 찾고, DNA1에서의 부분 서열을 찾아라
-	입력: I,j = 스코어의 위치, score = DNA1과 DNA2의 LCS score, gap = 각 위치가 어디서 파생된 값인지를 저장한 행렬, dna = DNA1, end = gap이나 mismatched가 마지막에 몇번 연속 되었는지를 저장, start = 문자열의 시작위치
-	출력: DNA1의 부분서열

(5)	String LCS_j(int I, int j, int **score, int ** gap, string dna, int *end. Int *start)
-	정의: DNA서열정렬방법과 현재 score를 활용하여 DNA1와 DNA2의 LCS를 찾고, DN2j에서의 부분 서열을 찾아라
-	입력: I,j = 스코어의 위치, score = DNA1과 DNA2의 LCS score, gap = 각 위치가 어디서 파생된 값인지를 저장한 행렬, dna = DNA2, end = gap이나 mismatched가 마지막에 몇번 연속 되었는지를 저장, start = 문자열의 시작위치
-	출력: DNA2의 부분서열
2.	풀이방법
(1)	Scoring(다이나믹 프로그래밍)
-	Score가 행렬에서 자신의 row-1, col-1, (row-1, col-1)중 제일 높은 값에서 파생된다는 점을 착안하여 다이나믹 프로그래밍을 적용한다. (먼저 계산한 값을 현재 값에 반영한다.)
(2)	LCS Search
-	현재 스코어 위치에 있는 gap을 확인하여 어느 위치에서 파생했는지를 찾고, 파생된 위치로 이동하는 것을 반복한다. 두 서열 중 한 서열이 끝이거나 gap 혹은 mismatched가 5번 이상 연속되면 Search의 끝이고, 이 끝은 부분서열의 시작 점이 되고, Search의 시작점은 부분서열의 끝이 된다. 
3.	문제점
(1)	부분 서열의 중복
-	최고 점수를 받은 5개 중 2개가 43점, 40점이라면 40점을 받은 부분서열이 43점을 받은 부분 서열의 substring일 가능성이 있고, 같은 점수를 받은 부분 서열 중 하나가 gap으로 뛰어넘고, 다른 하나는 mismatched로 뛰어 넘었을 수도 있다. (예: (ACGG, AGGG)와 (ACCG, A-GG) ) 이 문제의 경우 또다른 2차원 행렬을 만들어 이미 지나간 위치를 표시하고, LCS Search전에 위치가 이미 지나간 위치이고, 부분 수열의 끝점이라면 상위 부분 수열에 포함 시키지 않게 구현하면 될 것이다.
(2)	LCS가 상위 5개보다 적을 경우
-	이 문제는 (1)의 문제에서 파생된 것을 제외하고 논하자면 현재 코드는 무조건 5개의 상위 부분 수열을 출력하게 되어있어 만약 저장된 수열이 4개라면 에러가 발생한다. 이는 상위 부분 수열의 개수를 count하는 변수를 사용한다면 해결 가능할 것으로 생각된다.
