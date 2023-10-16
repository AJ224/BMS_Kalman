class KalmanFilter:
    def __init__(self, x, P, Q, R):
        self.x = x   # Initial state estimate
        self.P = P   # Initial error covariance
        self.Q = Q   # Process noise covariance
        self.R = R   # Measurement noise covariance
    def predict(self):
        self.x = self.x
        self.P = self.P + self.Q
        print("from predict:", self.x)
        return self.x

    def update(self, z):
        y = z - self.x
        S = self.P + self.R
        K = self.P / S
        print("Kalman Gain: ", K)
        self.x = self.x + K * y
        self.P = (1 - K) * self.P
        print("Error Covarince: ", self.P)
def main():
    # Initial state estimate and covariance
    x = float(input("Enter the initial State of Charge (SOC): "))
    P = 1.0
    # Process noise covariance and measurement noise covariance
    Q = 0.1
    R = 0.1
    kalman_filter = KalmanFilter(x, P, Q, R)
    while True:
        # Prompt the user to input the current SOC
        print("-----------------------------------")

        z1 = float(input("Enter the Measured Voltage: "))
        z = ((z1-40)/19.2)*100
        print(z)
        if z<=100 and z>=0:
            predicted_soc = kalman_filter.predict()
            kalman_filter.update(z)
            print(f"Estimated SOC: {predicted_soc}, Measured SOC: {z}")
        else:
            print("Invalid Input")
if __name__ == "__main__":
    main()
