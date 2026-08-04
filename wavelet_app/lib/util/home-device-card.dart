import 'package:Wavelet/theme/colors.dart';
import 'package:flutter/material.dart';

  enum DeviceStatus {
    offline,
    idle,
    playing
  }

class HomeDeviceCard extends StatefulWidget {
  HomeDeviceCard({
    super.key,
    required this.deviceName,
    required this.volume,
    required this.songName,
    required this.artistName,
    required this.deviceStatus
    
    });

  @override
  State<HomeDeviceCard> createState() => _HomeDeviceCardState();

  String deviceName;
  String volume;
  String songName;
  String artistName;
  DeviceStatus deviceStatus;

}

class _HomeDeviceCardState extends State<HomeDeviceCard> {
  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        color: WaveletColors.surfaceVariant(context),
        borderRadius: BorderRadius.circular(24),
        border: Border.all(
          color: WaveletColors.border(context),
          width: 0.8
        )
      ),

      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        mainAxisAlignment: MainAxisAlignment.start,

        children: [

          Row(
            children: [
              Image.asset(
                'assets/images/spk-temp,png',
              ),

              Column(
                children: [
                  Text(
                    widget.deviceName,
                    
                  )
                ],
              )


            ],
          )


        ], //end of column
      ),
    );
  }
}