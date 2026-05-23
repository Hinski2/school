X = csvread('z0905.csv');
lambda_z_daszkiem = mean(X);

printf("estymator mle: %f\n", lambda_z_daszkiem);