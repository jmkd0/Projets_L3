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

function [G]=rvb2ng(X)
    R=X(:,:,1);
    V=X(:,:,2);
    B=X(:,:,3);
    G=imlincomb(0.299,R,0.587,V,0.114,B);
endfunction
function [Y]=agrandirImage(X,T)
    [L,C]=size(X);
    Y=[];
    for i=1:T:T+L
        for j=1:T:T+C
            for a=i:i+T-1
                for b=j:j+T-1
                    Y(a,b)=X(i,j)
                end
            end
        end
    end
endfunction

function [Y]=agrandir(X,T)
    [L,C]=size(X);
    Y=[];
    for x=1:L
        for y=1:C
            for i=x*T:(x+1)*T
                for j=y*T:(y+1)*T
                    Y(i,j)=X(x,y);
                end
            end
        end
    end
endfunction

function Y=convolution(Image, Filtre)
    [lineImage, colomnImage]=size(Image);
    [lineFilter, colomnFilter]=size(Filtre);
    Y=conv2(X, Filtre);
endfunction



function [Y]=rotationImage(X,a)
    a=a*%pi/180;
    [ligne, colonne]=size(X);
    ligneResultat=ligne*cos(a);
    colonneResultat=colonne*sin(a)+ligne*cos(a);
    Y=[];
    Y=zeros(ligneResultat, colonneResultat);
    for i=1:ligne
        for j=1:colonne
            x=round(i*cos(a)-j*sin(a));
            y=round(j*sin(a)+i*cos(a));
            Y(x,y)=x;
        end
    end
endfunction
