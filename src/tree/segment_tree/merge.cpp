int merge(int o1, int o2, int fa, int l, int r){
      if(o1 == 0 || o2 == 0)   return o1 ^ o2;
      if(l == r){
          ans[fa] = max(ans[fa], l);
          return o1;
      }
      int m = (l + r) >> 1;
      ls[o1] = merge(ls[o1], ls[o2], fa, lson);
      rs[o1] = merge(rs[o1], rs[o2], fa, rson);
      return o1;
}
