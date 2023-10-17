#include <stdio.h>

// Battery model structure
typedef struct {
    double capacity;        // Battery capacity in Ah
    double voltage_nominal; // Nominal battery voltage in V
} BatteryModel;

// Kalman filter structure
typedef struct {
    double Q;     // Process noise covariance
    double R;     // Measurement noise covariance
    double x_hat; // Initial SOC estimate
    double P;     // Initial estimation error covariance (adjust as needed)
} KalmanFilter;

// Function to predict SOC based on current
void predict(KalmanFilter *kf, double current, BatteryModel *battery) {
    double delta_soc = -current / (battery->capacity * 3600); // Convert current from mA to A and time to hours
    kf->x_hat += delta_soc;  // Update SOC estimation
    kf->P += kf->Q;         // Update estimation error covariance
}

// Function to update SOC using voltage measurement
void update(KalmanFilter *kf, double voltage_measurement, BatteryModel *battery) {
    double K = kf->P / (kf->P + kf->R); // Calculate Kalman gain
    kf->x_hat += K * (voltage_measurement / battery->voltage_nominal - kf->x_hat); // Update SOC estimate using voltage measurement
    kf->P = (1 - K) * kf->P; // Update estimation error covariance
}

int main() {
    // Initialize battery model
    BatteryModel battery;
    battery.capacity = 30.0;
    battery.voltage_nominal = 59.2;

    // Initialize Kalman filter with appropriate Q, R, and initial SOC
    KalmanFilter kalman_filter;
    kalman_filter.Q = 0.01;
    kalman_filter.R = 0.1;
    kalman_filter.x_hat = 0.5;
    kalman_filter.P = 0.01;

    // Simulate real-time input (replace this with actual data acquisition)
    while (1) {
        double voltage_measurement;
        double current_measurement;
        double coulomb_counted_soc;

        // Get voltage and current measurements from user input
        printf("Enter voltage measurement (V): ");
        scanf("%lf", &voltage_measurement);
        printf("Enter current measurement (A): ");
        scanf("%lf", &current_measurement);

        // Execute Coulomb counting to calculate SOC
        coulomb_counted_soc = kalman_filter.x_hat;
        printf("Coulomb Counting SOC: %.2f%%\n", coulomb_counted_soc);

        // Execute the Kalman filter
        predict(&kalman_filter, current_measurement, &battery);
        update(&kalman_filter, voltage_measurement, &battery);

        // Print the estimated SOC
        printf("Kalman Filter SOC: %.2f%%\n", kalman_filter.x_hat);
    }

    return 0;
}
