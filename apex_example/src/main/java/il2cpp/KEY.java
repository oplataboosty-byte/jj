package il2cpp;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Handler;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.graphics.drawable.GradientDrawable;

public class KEY extends Activity {

    private static native String name2();
    private static native String name3();
    private static native String name4();
    private static native String name5();
    private static native String name6();
    private static native String name7();
    private static native String name8();
    private static native String name9();
    private static native String key7();

    private static final String CORRECT_KEY = key7();
    private static final String GET_KEY_URL = "gg";

    public static void Start(final Context context) {
        final SharedPreferences sharedPreferences = context.getSharedPreferences("SavePref", 0);
        String struser = sharedPreferences.getString("Enter KEY", null);

        LinearLayout mainLayout = new LinearLayout(context);
        mainLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        mainLayout.setOrientation(LinearLayout.VERTICAL);
        mainLayout.setBackgroundColor(Color.parseColor("#141414"));
        mainLayout.setPadding(50, 50, 50, 50);

        TextView titleTextView = new TextView(context);
        titleTextView.setText(name2());
        titleTextView.setTextColor(Color.WHITE);
        titleTextView.setTextSize(26);
        titleTextView.setGravity(Gravity.CENTER);
        titleTextView.setTypeface(null, Typeface.BOLD);
        titleTextView.setPadding(0, 0, 0, 40);
        mainLayout.addView(titleTextView);

        LinearLayout inputLayout = new LinearLayout(context);
        inputLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        inputLayout.setOrientation(LinearLayout.VERTICAL);

        final EditText keyEditText = new EditText(context);
        keyEditText.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        keyEditText.setHint(name3());
        keyEditText.setHintTextColor(Color.WHITE);
        keyEditText.setTextColor(Color.WHITE);
        keyEditText.setTextSize(20);
        keyEditText.setPadding(20, 25, 20, 25);
        keyEditText.setBackgroundColor(Color.TRANSPARENT);
        if (struser != null && !struser.isEmpty()) {
            keyEditText.setText(struser);
        }
        keyEditText.setGravity(Gravity.BOTTOM);
        inputLayout.addView(keyEditText);

        View underline = new View(context);
        underline.setLayoutParams(new LinearLayout.LayoutParams(-1, 3));
        underline.setBackgroundColor(Color.parseColor("#555555"));
        inputLayout.addView(underline);
        mainLayout.addView(inputLayout);

        Button loginButton = new Button(context);
        loginButton.setLayoutParams(new LinearLayout.LayoutParams(-1, 120));
        loginButton.setText(name4());
        loginButton.setTextColor(Color.WHITE);
        loginButton.setTextSize(20);
        loginButton.setTypeface(null, Typeface.BOLD);
        loginButton.setGravity(Gravity.CENTER);
        GradientDrawable gd = new GradientDrawable();
        gd.setColor(Color.parseColor("#9C27B0"));
        gd.setCornerRadius(10);
        loginButton.setBackground(gd);
        mainLayout.addView(loginButton);

        Button getKeyButton = new Button(context);
        getKeyButton.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        getKeyButton.setText(name5());
        getKeyButton.setTextColor(Color.WHITE);
        getKeyButton.setTextSize(18);
        getKeyButton.setGravity(Gravity.CENTER);
        getKeyButton.setPadding(30, 30, 30, 30);
        getKeyButton.setBackgroundColor(Color.TRANSPARENT);
        mainLayout.addView(getKeyButton);

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setView(mainLayout);
        builder.setCancelable(false);
        final AlertDialog alertDialog = builder.create();
        alertDialog.show();

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String key = keyEditText.getText().toString().trim();
                if (key.equals(CORRECT_KEY)) {
                    SharedPreferences.Editor edit = sharedPreferences.edit();
                    edit.putString("Enter KEY", key);
                    edit.apply();
                    alertDialog.dismiss();
                    Toast.makeText(context, name6(), Toast.LENGTH_SHORT).show();
                    Toast.makeText(context, name7(), Toast.LENGTH_SHORT).show();
                    new Handler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            Main.start(context);
                        }
                    }, 4700);
                } else {
                    keyEditText.setHintTextColor(Color.RED);
                    keyEditText.setHint(name8());
                    keyEditText.setText("");
                    Toast.makeText(context, name9(), Toast.LENGTH_SHORT).show();
                }
            }
        });

        getKeyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(GET_KEY_URL));
                context.startActivity(browserIntent);
            }
        });
    }
}
