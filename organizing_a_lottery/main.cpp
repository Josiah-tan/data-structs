#include"template.h"
#include"cassert"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

bool sort_segments_ascend(pair<int, int> a, pair<int, int> b){
	if (a.first == b.first){
		return a.second > b.second;
	}
	return a.first < b.first;
}

vector<int> solution(vector<pair<int, int>>& segments, vector<int>& points){
	vector<pair<int, int>> segments_counter(segments.size() * 2);
	vector<pair<int, int>>	points_index(points.size());
	for (unsigned int i = 0; i < points.size(); i++){
		// just an FYI for myself: points_index.push_back({points[i], i});
		points_index[i].first = points[i];
		points_index[i].second = i;
	}
	for (unsigned int i = 0; i < segments.size(); i++){
		segments_counter[i].first = segments[i].first;
		segments_counter[i].second = 1;
		segments_counter[segments_counter.size() - i - 1].first = segments[i].second + 1;
		segments_counter[segments_counter.size() - i - 1].second = -1;
	}

	sort(points_index.begin(), points_index.end());
	sort(segments_counter.begin(), segments_counter.end(), sort_segments_ascend);
	
	// for (unsigned int i = 0; i < points.size(); i++){
	// 	cout << points[i].first << " " << points[i].second << endl;
	// }
	// for (unsigned int i = 0; i < segments_counter.size(); i++){
	// 	cout << segments_counter[i].first << " " << segments_counter[i].second << endl;
	// }

	vector<int>ans(points.size(), 0);
	unsigned int j = 0;
	int count = 0;
	for (unsigned int i = 0; i < points.size(); i++){
		while (j < segments_counter.size() && segments_counter[j].first <= points_index[i].first){
			count += segments_counter[j].second;
			j++;
		}
		ans[points_index[i].second] = count;
	}
	return ans;
}

vector<int> NumberOfSegments(vector<pair<int,int> >segments, vector<int>points){
	int s = segments.size();
	int p = points.size();
   vector< pair<int, int> >pts, seg;
     
   // Pushing points and index in
   // vector as a pairs
   for(int i = 0; i < p; i++)
   {
      pts.push_back({points[i], i});;
   }
     
   for(int i = 0; i < s; i++)
   {
      // (l,+1)
      seg.push_back({segments[i].first, 1});
      // (r+1,-1)
      seg.push_back({segments[i].second+1, -1});
   }
     
   // Sort the vectors
   sort(seg.begin(), seg.end(),
        greater<pair<int,int>>());
   sort(pts.begin(),pts.end());
	 
	// for (unsigned int i = 0; i < pts.size(); i++){
	// 	cout << pts[i].first << " " << pts[i].second << endl;
	// }
	// for (unsigned int i = 0; i < seg.size(); i++){
	// 	cout << seg[i].first << " " << seg[i].second << endl;
	// }
     
   int count = 0;
   vector<int> ans(p);
     
   for(int i = 0; i < p; i++)
   {
        int x = pts[i].first;
        
        while(!seg.empty() &&
              seg.back().first <= x)
        {
            count+= seg.back().second;
            seg.pop_back();
        }
        ans[pts[i].second] = count;
   }
	 return ans;
}

int main(void){
	int s, p;
	cin >> s >> p;
	vector<pair<int, int>> segments(s);
	for (int i = 0; i < s; i++){
		cin >> segments[i].first >> segments[i].second;
	}
	vector<int> points(p);
	for (int i = 0; i < p; i++){
		cin >> points[i];
	}
	vector<int>ans = solution(segments, points);
	// vector<int>ans = NumberOfSegments(segments, points);
	for (unsigned int i = 0; i < ans.size(); i++){
		cout << ans[i] << " ";
	}
}

