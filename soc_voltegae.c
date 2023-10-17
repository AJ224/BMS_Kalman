#include <stdio.h>

// Kalman filter structure
typedef struct {
    double x; // Initial state estimate
    double P; // Initial error covariance
    double Q; // Process noise covariance
    double R; // Measurement noise covariance
} KalmanFilter;

// Function to predict SOC
double predict(KalmanFilter *kf) {
    kf->x = kf->x;
    kf->P = kf->P + kf->Q;
    printf("from predict: %.2f\n", kf->x);
    return kf->x;
}

// Function to update SOC
void update(KalmanFilter *kf, double z) {
    double y = z - kf->x;
    double S = kf->P + kf->R;
    double K = kf->P / S;
    printf("Kalman Gain: %.2f\n", K);
    kf->x = kf->x + K * y;
    kf->P = (1 - K) * kf->P;
    printf("Error Covariance: %.2f\n", kf->P);
}

int main() {
    // Initial state estimate and covariance
    double x = 50;
    //printf("Enter the initial State of Charge (SOC): ");
    //scanf("%lf", &x);

    double P = 1.0;

    // Process noise covariance and measurement noise covariance
    double Q = 0.1;
    double R = 0.1;

    KalmanFilter kalman_filter;
    kalman_filter.x = x;
    kalman_filter.P = P;
    kalman_filter.Q = Q;
    kalman_filter.R = R;

    while (1) {
        printf("-----------------------------------\n");
        double z1;
        printf("Enter the Measured Voltage: ");
        scanf("%lf", &z1);
        double z = ((z1 - 40) / 19.2) * 100;

        if (z <= 100 && z >= 0) {
            double predicted_soc = predict(&kalman_filter);
            update(&kalman_filter, z);
            printf("Estimated SOC: %.2f, Measured SOC: %.2f\n", predicted_soc, z);
        } else {
            printf("Invalid Input\n");
        }
    }

    return 0;
}
