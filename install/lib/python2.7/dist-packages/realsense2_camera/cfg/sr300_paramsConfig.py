## *********************************************************
##
## File autogenerated for the realsense2_camera package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'upper': 'DEFAULT', 'lower': 'groups', 'srcline': 245, 'name': 'Default', 'parent': 0, 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'cstate': 'true', 'parentname': 'Default', 'class': 'DEFAULT', 'field': 'default', 'state': True, 'parentclass': '', 'groups': [], 'parameters': [{'srcline': 292, 'description': 'Backlight Compensation', 'max': 4, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_backlight_compensation', 'edit_method': '', 'default': 0, 'level': 1, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Brightness', 'max': 64, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_brightness', 'edit_method': '', 'default': 0, 'level': 2, 'min': -64, 'type': 'int'}, {'srcline': 292, 'description': 'Contrast', 'max': 100, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_contrast', 'edit_method': '', 'default': 50, 'level': 3, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Gain', 'max': 128, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_gain', 'edit_method': '', 'default': 64, 'level': 4, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Gamma', 'max': 500, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_gamma', 'edit_method': '', 'default': 300, 'level': 5, 'min': 100, 'type': 'int'}, {'srcline': 292, 'description': 'Hue', 'max': 180, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_hue', 'edit_method': '', 'default': 0, 'level': 6, 'min': -180, 'type': 'int'}, {'srcline': 292, 'description': 'Saturation', 'max': 100, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_saturation', 'edit_method': '', 'default': 64, 'level': 7, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Sharpness', 'max': 100, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_sharpness', 'edit_method': '', 'default': 50, 'level': 8, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'White Balance', 'max': 6500, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_white_balance', 'edit_method': '', 'default': 4600, 'level': 9, 'min': 2800, 'type': 'int'}, {'srcline': 292, 'description': 'Enable Auto White Balance', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_enable_auto_white_balance', 'edit_method': '', 'default': True, 'level': 10, 'min': False, 'type': 'bool'}, {'srcline': 292, 'description': 'Exposure', 'max': 10000, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_exposure', 'edit_method': '', 'default': 156, 'level': 11, 'min': 39, 'type': 'int'}, {'srcline': 292, 'description': 'Enable Auto Exposure', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_color_enable_auto_exposure', 'edit_method': '', 'default': True, 'level': 12, 'min': False, 'type': 'bool'}, {'srcline': 292, 'description': 'SR300 Visual Presets', 'max': 10, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_visual_preset', 'edit_method': "{'enum_description': 'SR300 Visual Presets', 'enum': [{'srcline': 29, 'description': 'Short Range', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 0, 'ctype': 'int', 'type': 'int', 'name': 'ShortRange'}, {'srcline': 30, 'description': 'Long Range', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 1, 'ctype': 'int', 'type': 'int', 'name': 'LongRange'}, {'srcline': 31, 'description': 'Background Segmentation', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 2, 'ctype': 'int', 'type': 'int', 'name': 'BackgroundSegmentation'}, {'srcline': 32, 'description': 'Gesture Recognition', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 3, 'ctype': 'int', 'type': 'int', 'name': 'GestureRecognition'}, {'srcline': 33, 'description': 'Object Scanning', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 4, 'ctype': 'int', 'type': 'int', 'name': 'ObjectScanning'}, {'srcline': 34, 'description': 'Face Analytics', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 5, 'ctype': 'int', 'type': 'int', 'name': 'FaceAnalytics'}, {'srcline': 35, 'description': 'Face Login', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 6, 'ctype': 'int', 'type': 'int', 'name': 'FaceLogin'}, {'srcline': 36, 'description': 'GR Cursor', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 7, 'ctype': 'int', 'type': 'int', 'name': 'GrCursor'}, {'srcline': 37, 'description': 'Default', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 8, 'ctype': 'int', 'type': 'int', 'name': 'Default'}, {'srcline': 38, 'description': 'Mid Range', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 9, 'ctype': 'int', 'type': 'int', 'name': 'MidRange'}, {'srcline': 39, 'description': 'IR Only', 'srcfile': '/home/antonyhwang/infinitam_ws/src/realsense2_camera/cfg/sr300_params.cfg', 'cconsttype': 'const int', 'value': 10, 'ctype': 'int', 'type': 'int', 'name': 'IrOnly'}]}", 'default': 8, 'level': 13, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Laser Power', 'max': 16, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_laser_power', 'edit_method': '', 'default': 16, 'level': 14, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Accuracy', 'max': 3, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_accuracy', 'edit_method': '', 'default': 1, 'level': 15, 'min': 1, 'type': 'int'}, {'srcline': 292, 'description': 'Motion Range', 'max': 220, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_motion_range', 'edit_method': '', 'default': 9, 'level': 16, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Filter Option', 'max': 7, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_filter_option', 'edit_method': '', 'default': 5, 'level': 17, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Confidence Threshold', 'max': 15, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_confidence_threshold', 'edit_method': '', 'default': 3, 'level': 18, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Frames Queue Size', 'max': 32, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_frames_queue_size', 'edit_method': '', 'default': 16, 'level': 19, 'min': 0, 'type': 'int'}, {'srcline': 292, 'description': 'Depth Units', 'max': 0.000124987, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/kinetic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'sr300_depth_units', 'edit_method': '', 'default': 0.000124987, 'level': 20, 'min': 0.000124987, 'type': 'double'}], 'type': '', 'id': 0}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

sr300_params_ShortRange = 0
sr300_params_LongRange = 1
sr300_params_BackgroundSegmentation = 2
sr300_params_GestureRecognition = 3
sr300_params_ObjectScanning = 4
sr300_params_FaceAnalytics = 5
sr300_params_FaceLogin = 6
sr300_params_GrCursor = 7
sr300_params_Default = 8
sr300_params_MidRange = 9
sr300_params_IrOnly = 10
