"""
RNAのfoldingを予測する。
"""
class Nussinov:
    def __init__(self):
        self.bp = [("a","u"),("c","g"),("g","u")]
        self.bp_min_inner_base = 3
    
    def set_sequence(self, seq):
        self.seq = seq.lower()
        self.len_seq = len(seq)
    
    def nussinov(self):
        self.num_bp = [[0] * self.len_seq for _ in range(self.len_seq)]
        for inner_base in range(self.bp_min_inner_base, self.len_seq):
            for l in range(0, self.len_seq - inner_base - 1):
                r = l + inner_base + 1
                delta = (self.seq[l],self.seq[r]) in self.bp or (self.seq[r],self.seq[l]) in self.bp
                self.num_bp[l][r] = max(self.num_bp[l+1][r], self.num_bp[l][r-1], self.num_bp[l+1][r-1] + delta)
                for k in range(l, r):
                    if self.num_bp[l][k] + self.num_bp[k + 1][r] > self.num_bp[l][r]:
                        self.num_bp[l][r] = self.num_bp[l][k] + self.num_bp[k + 1][r]
        return self.num_bp
    
    def traceback(self):
        stack = [(0, self.len_seq - 1)]
        bp_list = ["."] * self.len_seq
        while stack:
            l, r = stack.pop()
            if l >= r:
                continue
            delta = (self.seq[l],self.seq[r]) in self.bp or (self.seq[r],self.seq[l]) in self.bp
            if self.num_bp[l][r] == self.num_bp[l + 1][r]:
                stack.append((l + 1, r))
            elif self.num_bp[l][r] == self.num_bp[l][r - 1]:
                stack.append((l, r - 1))
            elif self.num_bp[l][r] == self.num_bp[l + 1][r - 1] + delta:
                bp_list[l] = "("
                bp_list[r] = ")"
                stack.append((l + 1, r - 1))
            else:
                for k in range(l, r):
                    if self.num_bp[l][r] == self.num_bp[l][k] + self.num_bp[k + 1][r]:
                        stack.append((k + 1, r))
                        stack.append((l, k))
                        break
        self.structure = "".join(bp_list)
        return self.structure
        

if __name__=="__main__":
    S = Nussinov()
    seq = "ACGUUCGUAGCUCAAUAGGUUAGAGCAUUACCAUGACAUGGUAGAGGUUAGUGGUUCAAGUCCACUCGAACGUA"
    S.set_sequence(seq)
    S.nussinov()
    print(S.traceback())