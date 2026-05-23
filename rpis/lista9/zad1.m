X = csvread('z0901.csv');
X_mean = mean(X);
n = length(X);

s2 = 0;
for i = 1:n
    s2 += (X(i) - X_mean)^2;
end
s2 = s2 / n;

printf("srednia: %f\n", X_mean);
printf("S^2: %f\n", s2);