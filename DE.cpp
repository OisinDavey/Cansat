#include<bits/stdc++.h>

//clock_t tStart = clock();	
//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

using namespace std;

ifstream infile;
ofstream outfile;

double K1,K2,K3;

double DE(double output){
	if(output >=0)
		return (-K2+sqrt(K2*K2-4*K1*(K3-output)))/(2*K1);
	else
		return -1*(-K2+sqrt(K2*K2-4*K1*(K3+output)))/(2*K1);
}

vector<double> parse(){
	double v[10];
	vector<double> V;
	string s;
	double x;
	infile >> s >> s >> s >> s >> v[0] >> v[1] >> v[2] >> s >> s >> v[3] >> s >> s >> v[4] >> s >> s >> v[5] >> s >> s >> v[6];
	for(int i=0;i<7;++i)
		V.push_back(v[i]);
	return V;
}

int main(){
	srand (time(NULL));
	string S1,S2;
	cout << "Input File :\n";
	cin >> S1;
	cout << "Output File :\n";
	cin >> S2;
	infile.open(S1);
	outfile.open(S2);
	//ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
	while(1){
		vector<double> v;
		char x;
		string SS;
		infile >> x;
		if(infile.eof()){
			break;
		}else if(x == '!'){
			v = parse();
			K1 = v[0];
			K2 = v[1];
			K3 = v[2];
			for(int i=3;i<v.size();++i)
				outfile << fixed  << setprecision(8) << DE(v[i]) << ' ';
			outfile << endl;
		}else{
			getline(infile,SS);
		}
	}
}