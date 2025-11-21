"""
attitude.py - MPU6050 IMU Attitude Visualization

3D visualization tool that renders a rotating cube based on real-time
accelerometer data from an STM32-connected MPU6050 IMU. Uses a pinhole
camera projection model to display the cube's orientation matching the
physical sensor's attitude.

Reads IMU data (ax, ay, az, gx, gy, gz) over serial and computes roll/pitch
angles to rotate the cube accordingly.

Dependencies: pygame, numpy, pyserial
"""

import pygame
import numpy as np
import math
import serial
import sys

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
Z_OFFSET = 5
FOCAL_LENGTH = 5

CAMERA = np.array([0, 0, 0])

# Define cube vertices
CUBE_VERTICES = [
  np.array([-1, -1, Z_OFFSET]),
  np.array([1, -1, Z_OFFSET]),
  np.array([-1, 1, Z_OFFSET]),
  np.array([-1, -1, Z_OFFSET + 2]),
  np.array([1, 1, Z_OFFSET]),
  np.array([-1, 1, Z_OFFSET + 2]),
  np.array([1, -1, Z_OFFSET + 2]),
  np.array([1, 1, Z_OFFSET + 2])
]

# Rotation matrices
def rotation_x(angle):
  return np.array([
    [1, 0, 0],
    [0, math.cos(angle), -math.sin(angle)],
    [0, math.sin(angle), math.cos(angle)]
  ])

def rotation_y(angle):
  return np.array([
    [math.cos(angle), 0, math.sin(angle)],
    [0, 1, 0],
    [-math.sin(angle), 0, math.cos(angle)]
  ])

def rotation_z(angle):
  return np.array([
    [math.cos(angle), -math.sin(angle), 0],
    [math.sin(angle), math.cos(angle), 0],
    [0, 0, 1]
  ])

class Engine:
  def __init__(self, port):
    self.window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Rotating Cube (Pinhole Camera)")
    self.angle = 0.0
    self.clock = pygame.time.Clock()
    self.cube_center = np.mean(CUBE_VERTICES, axis=0)
    self.imu_vals = None

    # IMU serial init
    baud = 115200
    self.ser = serial.Serial(port, baud, timeout=1)

  def update(self):
     # Get serial output
     # ax, ay, az, gx, gy, gz
    line = self.ser.readline().decode('utf-8').strip()

    if line:
      self.imu_vals = [float(v) for v in line.split(",")]

  def draw(self):
    self.window.fill((0,0,0))

    # rotation matrix around both x and y
    if not self.imu_vals:
      return
    
    ax, ay, az = self.imu_vals[:3]
    mag = (ax**2 + ay**2 + az**2)**(1/2)
    ax_degrees = -90 * ax / mag
    ay_degrees = -90 * ay / mag
    ax_radians = math.radians(ax_degrees)
    ay_radians = math.radians(ay_degrees)
    R = rotation_x(ay_radians) @ rotation_z(ax_radians)
  
    # apply rotation around cube center
    rotated_vertices = []
    for v in CUBE_VERTICES:
      shifted = v - self.cube_center
      rotated = R @ shifted + self.cube_center
      rotated_vertices.append(rotated)

    # draw edges
    for i, p1 in enumerate(rotated_vertices):
      for j, p2 in enumerate(rotated_vertices):
        if np.linalg.norm(p1 - p2) <= 2.1:  # crude edge test
          x1, y1, z1 = p1
          x2, y2, z2 = p2

          xp1, yp1 = FOCAL_LENGTH * x1 / z1, FOCAL_LENGTH * y1 / z1
          xp2, yp2 = FOCAL_LENGTH * x2 / z2, FOCAL_LENGTH * y2 / z2

          X1, Y1 = SCREEN_WIDTH / 2 + xp1 * 100, SCREEN_HEIGHT / 2 + yp1 * 100
          X2, Y2 = SCREEN_WIDTH / 2 + xp2 * 100, SCREEN_HEIGHT / 2 + yp2 * 100

          pygame.draw.line(self.window, (255,255,255), (X1,Y1), (X2,Y2), 1)

    pygame.display.flip()
    self.clock.tick(60)

  def run(self):
    running = True
    while running:
      for e in pygame.event.get():
        if e.type == pygame.QUIT:
          running = False
      self.update()
      self.draw()

def main():
  if len(sys.argv) != 2:
    print(f"Usage: python {sys.argv[0]} <serial_port>")
    print(f"Example: python {sys.argv[0]} /dev/cu.usbserial-120")
    sys.exit(1)

  port = sys.argv[1]
  engine = Engine(port)
  engine.run()

if __name__ == "__main__":
  main()
