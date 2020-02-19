#include <iostream>
typedef long long ll;

const ll P=1e9+7;
ll _p(ll x, ll k) { return !k?1:_p(x, k/2)*_p(x, k/2)%P*(k&1?x:1)%P; }
ll inv(ll x) { return _p(x, P-2); }

ll R, G, B, K;

int main() {
	int Q; scanf("%d", &Q);
	while (Q--) std::cin>>R>>G>>B>>K, std::cout<<(((K*(B+G)%P*inv(B)+R*(1-_p(B*inv(B+1)%P, K)))%P+P)%P)<<'\n';
	return 0;
}