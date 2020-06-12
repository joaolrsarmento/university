format long
f=@(x) 1 ./ (1 + 7 * x.^2); % Function definition
X = [0 0.4 0.65 1.31 1.48 1.62 2.45]; Y = [1 0.471698 0.252685 0.076848 0.0612265 0.051624 0.0232463]; 
XX = [0.22 0.47 1.09 1.36 1.92]; % Values the program wanna calculate
for i = 1:length(XX) % Calculates the value for each value in XX
    xx = XX(i); value = SplineCubicaN(X, Y, xx); erro = abs(value - f(xx))/ abs(f(xx));
    fprintf('f(%.2f) = %.5f\nS3(%.2f) = %.5f\nErro relativo = %.5f\n', xx, f(xx), xx, value, erro); 
end
function[val]=SplineCubicaN(x,y,xx)
    n=length(x)-1; m = n - 1; h = zeros(1,m+1);
    for i = 0:m
        h(i+1) = x(i+2) - x(i+1);
    end
    A=zeros(n-1,n-1); A(1,1)=1; A(length(x),length(x))=1;
    for i=2:n
        for j=2:n
            if i==j
                A(i,j)=2*(h(i-1)+h(i)); A(i,j-1)=h(i-1); A(i,j+1)=h(i);
            end
        end
    end
    b=zeros(length(x),1);
    for i=2:n
        b(i,1)=6*(((y(i+1)-y(i))/(h(i)))-((y(i)-y(i-1))/(h(i-1))));
    end
    g=A\b; i=1;
    for k=1:length(x)-1
        ak(k)=(g(k+1,1)-g(k))/(6*h(k)); bk(k)=g(k+1)/2; ck(k)=((y(k+1)-y(k))/h(k))+(2*h(k)*g(k+1)+g(k)*h(k))/6; dk(k)=y(k+1);
    end
    while xx>x(i+1)
        i=i+1;
    end
    val=ak(i)*(xx-x(i+1)).^3+bk(i)*(xx-x(i+1)).^2+ck(i)*(xx-x(i+1))+dk(i);
end