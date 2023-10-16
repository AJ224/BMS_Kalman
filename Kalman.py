class BatteryModel:
    def __init__(self, capacity, nominal_voltage):
        self.capacity = capacity  # Battery capacity in Ah
        self.voltage_nominal = nominal_voltage  # Nominal battery voltage in V

class KalmanFilter:
    def __init__(self, Q, R, initial_soc):
        self.Q = Q  # Process noise covariance
        self.R = R  # Measurement noise covariance
        self.x_hat = initial_soc  # Initial SOC estimate
        self.P = 0.01  # Initial estimation error covariance (adjust as needed)

    def predict(self, current):
        # Calculate change in SOC based on current
        delta_soc = -current / (battery.capacity * 3600)  # Convert current from mA to A and time to hours
        self.x_hat += delta_soc #update SOC estimation
        self.P += self.Q # Update estimation error covariance

    def update(self, voltage_measurement):
        K = self.P / (self.P + self.R) # Calculate Kalman gain
        self.x_hat += K * (voltage_measurement / battery.voltage_nominal - self.x_hat) # Update SOC estimate using voltage measurement
        self.P = (1 - K) * self.P # Update estimation error covariance

# Initialize battery model
battery = BatteryModel(capacity=30.0, nominal_voltage=59.2)

# Initialize Kalman filter with appropriate Q, R, and initial SOC
kalman_filter = KalmanFilter(Q=0.01, R=0.1, initial_soc=0.5)

# Simulate real-time input (replace this with actual data acquisition)
while(1):
    voltage_measurement = float(input("Enter voltage measurement (V): "))
    current_measurement = float(input("Enter current measurement (A): "))
    coulomb_counted_soc = kalman_filter.x_hat # Execute Coulomb counting to calculate SOC
    print("Coulomb Counting SOC: {:.2%}".format(coulomb_counted_soc))
    # Execute the Kalman filter
    kalman_filter.predict(current_measurement)
    kalman_filter.update(voltage_measurement)
    # Print the estimated SOC
    print("Kalman Filter SOC: {:.2%}".format(kalman_filter.x_hat))

