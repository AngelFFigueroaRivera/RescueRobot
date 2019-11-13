using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace KinectHandTracking
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Members

        KinectSensor _sensor;
        MultiSourceFrameReader _reader;
        IList<Body> _bodies;
        SerialPort serial = new SerialPort("COM4", 9600);
        #endregion

        #region Constructor

        public MainWindow()
        {
            InitializeComponent();
        }

        #endregion

        #region Event handlers

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _sensor = KinectSensor.GetDefault();

            if (_sensor != null)
            {
                _sensor.Open();

                _reader = _sensor.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Depth | FrameSourceTypes.Infrared | FrameSourceTypes.Body);
                _reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if (_reader != null)
            {
                _reader.Dispose();
            }

            if (_sensor != null)
            {
                _sensor.Close();
            }
        }

        void Reader_MultiSourceFrameArrived(object sender, MultiSourceFrameArrivedEventArgs e)
        {
            var reference = e.FrameReference.AcquireFrame();

            // Color
            using (var frame = reference.ColorFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    camera.Source = frame.ToBitmap();
                }
            }

            // Body
            using (var frame = reference.BodyFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    canvas.Children.Clear();

                    _bodies = new Body[frame.BodyFrameSource.BodyCount];

                    frame.GetAndRefreshBodyData(_bodies);

                    foreach (var body in _bodies)
                    {
                        if (body != null)
                        {
                            if (body.IsTracked)
                            {
                                // Find the joints
                                Joint handRight = body.Joints[JointType.HandRight];
                                Joint thumbRight = body.Joints[JointType.ThumbRight];

                                Joint handLeft = body.Joints[JointType.HandLeft];
                                Joint thumbLeft = body.Joints[JointType.ThumbLeft];

                                Joint head = body.Joints[JointType.Head];
                                Joint neck = body.Joints[JointType.Neck];
                                Joint leftknee = body.Joints[JointType.KneeLeft];
                                Joint rightknee = body.Joints[JointType.KneeRight];
                                // Draw hands and thumbs
                                canvas.DrawHand(handRight, _sensor.CoordinateMapper);
                                canvas.DrawHand(handLeft, _sensor.CoordinateMapper);
                                canvas.DrawThumb(thumbRight, _sensor.CoordinateMapper);
                                canvas.DrawThumb(thumbLeft, _sensor.CoordinateMapper);

                                // Find the hand states
                                string rightHandState = "-";
                                string leftHandState = "-";

                                //Obtener la mano 

                                if (handRight.TrackingState == TrackingState.Tracked)
                                {
                                  //Detecta la mano derecha y see rellena con un circulo. 
                                   ColorSpacePoint dspRight = _sensor.CoordinateMapper.MapCameraPointToColorSpace(handRight.Position);
                                   Ellipse rightObject = new Ellipse(){Width = 60, Height = 60, Fill = new SolidColorBrush(Color.FromArgb(255,255,0,0))};
                                   canvas.Children.Add(rightObject);
                                   Canvas.SetLeft(rightObject, dspRight.X);
                                   Canvas.SetTop(rightObject, dspRight.Y);

                                    if (dspRight.X > 1500  & serial.IsOpen)
                                    {
                                        serial.Write("a");
                                        
                                    }
                                    else if (dspRight.X < 500 & serial.IsOpen)
                                    {
                                        serial.Write("b");
                                    }
                                    else if (dspRight.Y < 200 & serial.IsOpen)
                                    {
                                        serial.Write("c"); 
                                    }
                                    else if (dspRight.Y > 800 & serial.IsOpen)
                                    {
                                        serial.Write("d");
                                    }
                                    else if (dspRight.X > 501 & dspRight.X < 1499 & serial.IsOpen & dspRight.Y > 200 & dspRight.Y < 800) // & dspRight.Y > 1000   & dspRight.Y > 601 & serial.IsOpen)
                                    {
                                        serial.Write("e");
                                    }
                                   
                                }
                                switch (body.HandRightState)
                                {
                                    case HandState.Open:
                                        rightHandState = "Open";
                                        break;
                                    case HandState.Closed:
                                        rightHandState = "Closed";
                                   
                                        break;
                                    case HandState.Lasso:
                                        rightHandState = "Lasso";
                                       
                                        break;
                                    case HandState.Unknown:
                                        rightHandState = "Unknown...";
                                       
                                        break;
                                    case HandState.NotTracked:
                                        rightHandState = "Not tracked";
                                       
                                        break;
                                    default:
                                        break;
                                }

                                switch (body.HandLeftState)
                                {
                                    case HandState.Open:
                                        leftHandState = "Open";
                                        break;
                                    case HandState.Closed:
                                        leftHandState = "Closed";
                                        break;
                                    case HandState.Lasso:
                                        leftHandState = "Lasso";
                                        break;
                                    case HandState.Unknown:
                                        leftHandState = "Unknown...";
                                        break;
                                    case HandState.NotTracked:
                                        leftHandState = "Not tracked";
                                        break;
                                    default:
                                        break;
                                }

                                tblRightHandState.Text = rightHandState;
                                tblLeftHandState.Text = leftHandState;
                            }
                        }
                    }
                }
            }
        }

        #endregion

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            foreach(string s in SerialPort.GetPortNames())
            {
                cmbBox.Items.Add(s);
            }
        }

        private void cmbBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Console.WriteLine("ENTRÉ!!!!!!!!!");
            string portName = cmbBox.Text;

            try
            {
                serial.Open();
                Console.WriteLine("Abrí el puerto");


            }
            catch
            {
                Console.Write("NOOOOOOOOOOOOOOOOO");
                return;
            }
        }
    }
}
