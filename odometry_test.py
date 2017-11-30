import unittest
from odometry import Odometry

class OdometryTest(unittest.TestCase):
    """Test case utilisé pour tester les fonctions du module 'odometry'."""

    def test_init(self):

        """Test the initialisation of the odometry class"""
        vehicleLength = 2
        odometry = Odometry(vehicleLength)
        self.assertEqual(odometry.x, 0)
        self.assertEqual(odometry.y, 0)
        self.assertEqual(odometry.theta, 0)
        self.assertEqual(odometry.v, 0)
        self.assertEqual(odometry.vehicleLength, vehicleLength)

    def test_ForwardDriving(self):
        """Test le fonctionnement de la fonction 'update'."""
        vehicleLength = 2
        odometry = Odometry(vehicleLength)
        for i in range(2):
            odometry.update(0.020, 0.0, 10.0)
        self.assertNotEqual(odometry.x, 0)
        self.assertEqual(odometry.y, 0)
        self.assertEqual(odometry.theta, 0)
        self.assertNotEqual(odometry.v, 0)

if __name__ == '__main__':
    unittest.main()
