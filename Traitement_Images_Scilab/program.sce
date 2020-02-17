function [Y]=histog(X)
    Min=min(X);
    Max=max(X);
    [n,m]=size(X);
    Y=X;
    for i=1:n
        for j=1:m
            Y(i,j)=(255/(Max-Min))*(X(i,j)-Min);
        end
    end
endfunction
