import 'package:Wavelet/pages/initalpair/initial-pair-final_page.dart';
import 'package:Wavelet/pages/login_page.dart';
import 'package:flutter/material.dart';
import 'package:Wavelet/theme/colors.dart';

class HomePage extends StatefulWidget {
  HomePage({super.key, required this.toggleTheme});

  @override
  State<HomePage> createState() => _HomePageState();
  final VoidCallback toggleTheme; // add this

  List<String> devices = [];

}

class _HomePageState extends State<HomePage> {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: WaveletColors.background(context),
        body: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [

//profile, notif, greetings
            Row(

              children: [

                Column(
                  children: [
                    Text(
                      'Good afternoon',  //change to time specific later
                      style: TextStyle(
                        color: WaveletColors.textSecondary(context),
                        fontFamily: 'Inter',
                        fontSize: 14,
                        fontWeight: FontWeight.w400
                      ),
                    ),

                    SizedBox(height: 2,),

                    Text(
                      'Serenity',  //change to username
                      style: TextStyle(
                        color: WaveletColors.textPrimary(context),
                        fontFamily: 'Inter',
                        fontSize: 24,
                        fontWeight: FontWeight.w700
                      ),
                    )
                  ],
                ),

                SizedBox(width: 159,),

//notification bell
                IconButton(
                  onPressed: (){}, 
                  icon: Icon(
                    Icons.circle_notifications_rounded,
                    color: WaveletColors.textSecondary(context),
                    
                    ),

                    style: IconButton.styleFrom(
                      backgroundColor: WaveletColors.secondaryButton(context)
                    ),
                    ),

//profile icon
                  CircleAvatar(
                    radius: 100,
                    backgroundColor: WaveletColors.accent(context),
                    child: IconButton(
                      onPressed: () {},
                      icon: const Icon(Icons.person),
                      color: Colors.black,
                    ),
                  ),
              ],
            ),

            SizedBox(height: 41,),

//online, playing, device count
            Container(
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(16),
                color: WaveletColors.surfaceVariant(context),
                border: Border.all(
                  color: WaveletColors.border(context),
                  width: 0.8,
                )
              ),
              child: Row(
                
                children: [
                  SizedBox(width: 12,),

//online circle
                  Container(
                    width: 8,
                    height: 8,
                    decoration: BoxDecoration(
                      color: WaveletColors.success(context),
                      shape: BoxShape.circle,
                    ),
                  ),

                  SizedBox(width: 8,),

                  Text(
                    '2 online', //replace with device onl count
                    style: TextStyle(
                      fontFamily: 'Inter',
                      fontWeight: FontWeight.w600,
                      fontSize: 12,
                      color: WaveletColors.textPrimary(context)
                    ),
                  ),

                  SizedBox(width: 41.46,),


//divider
                  SizedBox(
                    height: 16,
                    child: VerticalDivider(
                      width: 1,
                      color: WaveletColors.divider(context),
                      
                    ),
                  ),

                  SizedBox(width: 12,),

                  Icon(Icons.music_note, color: Color(0xFFFF4D6D),),

                  SizedBox(width:8 ,),

                  Text(
                    '1 playing', //replace with device onl count
                    style: TextStyle(
                      fontFamily: 'Inter',
                      fontWeight: FontWeight.w600,
                      fontSize: 12,
                      color: WaveletColors.textPrimary(context)
                    ),
                  ),

                SizedBox(width: 32.48,),

//divider
                  SizedBox(
                    height: 16,
                    child: VerticalDivider(
                      width: 1,
                      color: WaveletColors.divider(context),
                      
                    ),
                  ),

                  SizedBox(width: 12,),

                  Icon(Icons.speaker, color: Color(0xFFC084B0),),

                  SizedBox(width: 8,),

                  Text(
                    '3 devices', //replace with device acc count
                    style: TextStyle(
                      fontFamily: 'Inter',
                      fontWeight: FontWeight.w600,
                      fontSize: 12,
                      color: WaveletColors.textPrimary(context)
                    ),
                  ),
                ], //end of info bar
              ),
            ),




          ], //end of column

          
        ),

    );
  }
}