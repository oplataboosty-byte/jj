package il2cpp.typefaces;
import il2cpp.Utils;
import android.content.Context;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.graphics.drawable.GradientDrawable;
import android.graphics.Color;

public class WeaveTitle extends LinearLayout {
	Context context;
	
	public int dpi(float dp) {
		float scale = context.getResources().getDisplayMetrics().density;
		return (int) (dp * scale + 0.5f);
	}
	
	public TextView title;
	
	public WeaveTitle(Context ctx, String titletext) {
		super(ctx);
		context = ctx;
		
		title = new TextView(context);
		{ // Title textview
			title.setText(titletext);
			title.setTextSize(11f);
			title.setTypeface(Utils.font(context));
			title.setTextColor(Color.parseColor("#FFFFFF"));
			title.setGravity(Gravity.CENTER);
			title.setPadding(11,0,11,0);
			
			GradientDrawable backg = new GradientDrawable();
			{ // Background text
				backg.setColor(-13487566);
				backg.setCornerRadius(5f);
				
				title.setBackgroundDrawable(backg);
			}
		}
		
		addView(title, -1, dpi(18));
		setGravity(Gravity.CENTER);
		setPadding(0,5,0,5);
		
		setLayoutParams(new LayoutParams(-1, -2));
	}
}
