# Template Project

Code prepared for sensor characterization. This code corresponds to [this ADJ](https://github.com/HyperloopUPV-H8/adj/tree/linear-sensor-characterization)

To use it, specify the pin to which the ADC you want to characterize is connected by setting the corresponding define at the beginning of the main code. Then compile the code and flash the board.

Connect to the control station using the indicated ADJ.

You have a command available where you can input the real value currently being measured by the ADC. Once you’ve entered at least two measurements, you’ll start seeing the slope and offset being updated with the corresponding characterization values. At the same time, you’ll be able to see the sensor reading adjusted according to the new characterization.

Once you’ve added as many measurements as you want, you can copy the final slope and offset. It’s best to take them directly from the logs, as they include more decimal places and are therefore more precise.