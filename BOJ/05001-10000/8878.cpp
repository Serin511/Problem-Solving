#include <bits/stdc++.h>
using namespace std;

int main() {
	double x, p, a=0, w[30005];
	scanf("%lf %lf", &x, &p);
	x/=100.0, p=(100.0-p)/p;
	w[0]=1; for (int i=1; i<=30000; i++) w[i]=w[i-1]*p;
	for (int i=0; i<=25000; i++) for (int j=0; j<=5000; j++) {
		double g=(1-w[i])/(1-w[i+j]);
		a=max(a, j*g-(1-x)*i*(1-g));
	}
	printf("%.12lf\n", a);
	return 0;
}