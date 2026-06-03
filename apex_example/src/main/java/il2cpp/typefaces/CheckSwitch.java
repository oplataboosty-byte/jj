package il2cpp.typefaces;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.os.Handler;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import il2cpp.Utils;
import il2cpp.typefaces.Menu;
import android.content.res.ColorStateList;

public class CheckSwitch extends LinearLayout {
	Context context;

	android.widget.CheckBox checkbox;
	public TextView title;
	public LinearLayout expand;

	public boolean isChecked = true;
	public Callback callback;
	public int colorMain = 0;

	public static interface Callback {
		public void onChanged(boolean checked);
	}


	public void setCallback(Callback call) {
		callback = call;
	}

	public void setText(String t) {
		title.setText(t);
	}

	public void setColor(int c) {
		GradientDrawable grad = new GradientDrawable();
		grad.setColor(Color.BLACK);
		grad.setCornerRadius(0f);
		grad.setStroke(0, colorMain);

		checkbox.setBackgroundDrawable(grad);
	}

	public CheckSwitch(Context ctx) {
		super(ctx);
		context = ctx;

		//colorMain = -11110977;
		setPadding(0,10,0,0);
		setOrientation(LinearLayout.HORIZONTAL);

		checkbox = new android.widget.CheckBox(context);
		{ // CheckBox creatcheckbox.setButtonTintList(checkbox, new ColorStateList(color1, color2));
			checkbox.setButtonTintList(ColorStateList.valueOf(-51401));//setButtonTintList
			checkbox.setGravity(Gravity.CENTER_VERTICAL | Gravity.LEFT);
			checkbox.setChecked(false);
			//	checkbox.setPadding(0,20,0,20);
			this.setOnClickListener(new OnClickListener() {
					public void onClick(View v) {
						//	setChecked(!isChecked);
						if(isChecked){
							isChecked=false;
							checkbox.setChecked(true);
						} else {
							isChecked=true;
							checkbox.setChecked(false);
						}
					}
				});

		}

		expand = new LinearLayout(context);
		{ // Expand line

			expand.setGravity(Gravity.CENTER_VERTICAL | Gravity.LEFT);

			expand.addView(checkbox, -2, -2);
		}

		title = new TextView(context);
		{ // Checkbox text
			title.setTextSize(12f);
			title.setTypeface(Utils.font(context));
			title.setTextColor(Color.WHITE);
			title.setGravity(Gravity.CENTER_VERTICAL);
			title.setPadding(4,0,0,0);
		}





		addView(expand, -2, Utils.dp(context, 20));
		addView(title, -1, -1);
		setLayoutParams(new LinearLayout.LayoutParams(-1, -2));

		//setChecked(false);
	}
}

