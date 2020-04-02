usage:
stereo_match <left_image> <right_image> [--algorithm=bm|sgbm|hh|sgbm3way] [--blocksize=<block_size>]
[--max-disparity=<max_disparity>] [--scale=scale_factor>] [-i=<intrinsic_filename>] [-e=<extrinsic_filename>]
[--no-display] [-o=<disparity_image>] [-p=<point_cloud_file>]

can use default arguments:
cv::CommandLineParser parser(argc, argv,
                                 "{@arg1||}{@arg2||}{help h||}{algorithm|hh|}{max-disparity|16|}{blocksize|21|}{no-display||}{scale|1|}{i|intrinsics.yml|}{e|extrinsics.yml|}{o|disparity.jpg|}{p|point|}");

then you can use:
./stereo_match left1.png right1.png
to get rectififed image,disparity,pointcloud file