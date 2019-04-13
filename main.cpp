#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int checkScore(int i, int j, string DNA1, string DNA2, int** score, int** gapArr);
int max(int i, int j, int k, int* gap);
void isTop5(int num, int** top5, int i, int j);
string LCS_i(int i, int j, int **score, int **gap, string dna, int *end, int *start);
string LCS_j(int i, int j, int **score, int **gap, string dna, int *end, int *start);

int main(int argc, char* argv[]) {
	string DNAName1;
	string DNAName2;
	string DNApatten1 = " ";
	string DNApatten2 = " ";
	string buffer;

	int** top5 = new int*[5];
	for (int i = 0; i < 5; i++) {
		top5[i] = new int[3];
	}

	ifstream inp1;
	inp1.open(argv[1]);

	ifstream inp2;
	inp2.open(argv[2]);
	
	ofstream out;
	out.open("output.align");

	getline(inp1, DNAName1);

	while (inp1 >> buffer) {
		DNApatten1 += buffer;
	}
	out << "sequence1:" << DNAName1 << endl;

	getline(inp2, DNAName2);

	while (inp2 >> buffer) {
		DNApatten2 += buffer;
	}
	out <<"sequence2:" << DNAName2 << endl;

	
	int** score = new int*[DNApatten1.size()];

	for (int i = 0; i < DNApatten1.size(); i++) {
		score[i] = new int[DNApatten2.size()];
	}

	int** gap = new int*[DNApatten1.size()];
	for (int i = 0; i < DNApatten1.size(); i++) {
		gap[i] = new int[DNApatten2.size()];
	}


	//scoring and check is gap
	for (int i = 0; i < DNApatten1.size(); i++) {
		for (int j = 0; j < DNApatten2.size(); j++) {
			gap[i][j] = checkScore(i, j, DNApatten1, DNApatten2, score, gap);
			isTop5(score[i][j], top5, i, j);
		}
	}
	
	int end = 0;
	for(int i = 0; i < 5; i++) {
		end = 0;
		int start1 = 0;
		out <<"part of sequence: " << top5[i][0] << '\n';		
		string buff = LCS_i(top5[i][1], top5[i][2], score, gap, DNApatten1, &end, &start1);
		buff.erase(0, end);

		end = 0;
		int start2 = 0;
                string buff2 = LCS_j(top5[i][1], top5[i][2], score, gap, DNApatten2, &end, &start2);
                buff2.erase(0, end);
		
		out << "sequence1: " << start1 << "..." << top5[i][1] << '\n';
//		cout << end << '\n';
		out << "sequence2: " << start2 << "..." << top5[i][2] << '\n';
		out << "data1 " << buff<< '\n';
		out << "data2 " <<  buff2 << '\n';
//		cout << end << '\n';
		out << '\n';
	}
	/*
	//print all score
	cout << '\n' << "Score Table:" << endl;
	for (int i = 0; i < (DNApatten1.size()); i++) {
		for (int j = 0; j < (DNApatten2.size()); j++) {
			cout << score[i][j] << " ";
			if (j == DNApatten2.size()-1) {
				cout << '\n';
			}
		}
	}
	
	//print score and postition
	cout << '\n' << "Top 5:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "점수: " << top5[i][0] << " I의 종료위치 :" << top5[i][1] << " J의 종료위치 :" << top5[i][2] << '\n';
	}

	
	//print gap
	cout << '\n' << "Gap Table:" << endl;
	for (int i = 0; i < (DNApatten1.size()); i++) {
		for (int j = 0; j < (DNApatten2.size()); j++) {
			cout << gap[i][j] << " ";
			if (j == DNApatten2.size() - 1) {
				cout << '\n';
			}
		}
	}
	*/
	return 0;
}

// set score and return that gap or not
int checkScore(int i, int j, string DNA1, string DNA2, int** score, int** gapArr) {
	int matchScore = 0; // matched -> 3, mismatched -> -2
	int gap = 0;
	int leftPenalty = 2;
	int topPenalty = 2;
	// (i, j)
	if (i != 0 && j != 0) {
		if (DNA1[i] == DNA2[j]) {
			matchScore = 3; // if matched, +3
		}
		else {
			matchScore = -2; // if mismatched -2
		}
		if (gapArr[i][j - 1] > 0) {
			leftPenalty = 5;
		}
		if (gapArr[i - 1][j] > 0) {
			topPenalty = 5;
		}
		score[i][j] = max(score[i - 1][j] - topPenalty, score[i - 1][j - 1] + matchScore, score[i][j - 1] - leftPenalty, &gap);
	}

	// (0, j)
	else if (i == 0 && j != 0) {
		score[i][j] = score[i][j - 1] - 2;
	}

	//(i, 0)
	else if (i != 0 && j == 0) {
		score[i][j] = score[i-1][j] - 2;
	}

	else if (i == 0 && j == 0) {
		score[i][j] = 0;
	}

	// score < 0 -> score = 0
	if (score[i][j] < 0) {
		score[i][j] = 0;
	}

	return gap;
 }

//find maximum number and check gap or not
int max(int i, int j, int k, int *gap) {
	int result = i;
	*gap = 1; // if top is max,  it is gap

	if (j >= result) {
		result = j; // if j is max, it isn't gap
		*gap = 0;
	}

	if (k > result) {
		result = k;
		*gap = 2; // if left is max,  it is gap
	}

	return result;
}

// store top 5
void isTop5(int num, int** top5, int i, int j) {
	int buffer = 0;
	for (int k = 0; k < 5; k++) {
		if (top5[k][0] < num) {
			buffer = top5[k][0]; //change score
			top5[k][0] = num;
			num = buffer;
			 
			buffer = top5[k][1]; //change i postition
			top5[k][1] = i;
			i = buffer;

			buffer = top5[k][2]; //change j position
			top5[k][2] = j;
			j = buffer;
		}
	}
}

string LCS_i(int i, int j, int **score, int **gap, string dna, int *end, int *start) {
	if (*end == 5) {
		string str = "";
		return str;
	}
	if (gap[i][j] == 0) {
		if (i == 0 || j == 0) {
			string str = "";
			return str;
		}
		if (score[i][j] == (score[i - 1][j - 1] + 3)) {
			*start = i;
			*end = 0;
		}
		else {
			*end += 1;
		}
		string str = LCS_i(i - 1, j - 1, score, gap, dna, end, start) + dna[i];
		return str;
	}
	else if (gap[i][j] == 1) {
		*end += 1;
		string str = LCS_i(i - 1, j, score, gap, dna, end, start) + dna[i];
		return str;
	}

	else if (gap[i][j] == 2) {
		*end += 1;
		string str = LCS_i(i, j-1, score, gap, dna, end, start) + "-";
		return str;
	}
}

string LCS_j(int i, int j, int **score, int **gap, string dna, int *end, int *start) {

	if (*end == 5) {
		string str = "";
		return str;
	}

	if (gap[i][j] == 0) {
		if (i == 0 || j == 0) {
			string str = "";
			return str;
		}
		if(score[i][j] == (score[i - 1][j - 1] + 3)){
			*start = j;
			*end = 0;
		}
		else {
			*end += 1;
		}
		string str = LCS_j(i - 1, j - 1, score, gap, dna, end, start) + dna[j];
		return str;
	}
	else if (gap[i][j] == 1) {
		*end += 1;
		string str = LCS_j(i - 1, j, score, gap, dna, end, start) + "-";
		return str;
	}

	else if (gap[i][j] == 2) {
		*end += 1;
		string str = LCS_j(i, j - 1, score, gap, dna, end, start) + dna[j];
		return str;
	}
}
