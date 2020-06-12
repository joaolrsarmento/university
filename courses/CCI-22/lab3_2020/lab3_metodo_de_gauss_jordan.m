Ab=[3 -0.1 -0.2 7.85; 0.1 7 -0.3 -19.3; 0.3 -0.2 10 71.4];
x = Gauss_Jordan(Ab);
fprintf("O resultado encontrado:"); display(x);
function[x]=Gauss_Jordan(Ab)
    [m,n]=size(Ab);
    for j=1:m
        for z=2:m
            if Ab(j,j)==0
                t=Ab(1,:);Ab(1,:)=Ab(z,:);
                Ab(z,:)=t;
            end
        end
        for i=j+1:m
            Ab(i,:)=Ab(i,:)-Ab(j,:)*Ab(i,j)/Ab(j,j);
        end
    end
    for j=m:-1:2
        for i=j-1:-1:1
            Ab(i,:)=Ab(i,:)-Ab(j,:)*Ab(i,j)/Ab(j,j);
        end
    end
    x = zeros(size(m,1));
    for s=1:m
        Ab(s,:)=Ab(s,:)/Ab(s,s);
        x(s)=Ab(s,n);
    end
end