/**
 * Description: LineContainer assuming both slopes and queries monotonic.
 * Time: O(1)
 * Source: Own
 * Verification: http://acm.hdu.edu.cn/diy/contest_showproblem.php?cid=36005&pid=1009
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=626
 */

#include "LineContainer.h"

struct LCdeque : deque<Line> { 
	void addBack(Line L) { // assume nonempty
		while (1) {
			auto a = bk; pop_back(); a.lst = a.last_gre(L);
			if (size() && bk.lst >= a.lst) continue;
			pb(a); break;
		}
		L.lst = INF; pb(L);
	}
	void addFront(Line L) {
		while (1) {
			if (!size()) { L.lst = INF; break; }
			if ((L.lst = L.last_gre(ft)) >= ft.lst) pop_front();
			else break;
		}
		push_front(L);
	}
	void add(T a, T b) { // line goes to one end of deque
		if (!size() || a <= ft.a) addFront({a,b,0});
		else assert(a >= bk.a), addBack({a,b,0});
	}
	int ord = 0; // 1 = x's come in increasing order, -1 = decreasing order
	T query(T x) { 
		assert(ord);
		if (ord == 1) { 
			while (ft.lst < x) pop_front();
			return ft.eval(x);
		} else {
			while(size()>1&&prev(prev(end()))->lst>=x)pop_back();
			return bk.eval(x);
		}
	}
};
