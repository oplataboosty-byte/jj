
package il2cpp;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Bundle;
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
	

    public static native void Check();
    private static String strUser;
    protected static native void KEY(Context VVVVSJSBSNS);
    protected static native void DDDDD(Context TTTTTT);

    // Ключ, который нужно ввести (измените на свой)
    private static final String CORRECT_KEY = key7();

    // Ссылка для кнопки "Получить ключ" (измените на свою)
    private static final String GET_KEY_URL = "gg";

    public static String getUserKEY(Context context) {
        final SharedPreferences sharedPreferences = context.getSharedPreferences("SavePref", 0);
        strUser = sharedPreferences.getString("Enter KEY", null);
        return strUser;
    }

    public static void Start(final Context context) {
        System.loadLibrary("gvraudio");
        System.loadLibrary("gvraudio");

        final SharedPreferences sharedPreferences = context.getSharedPreferences("SavePref", 0);
        String struser = sharedPreferences.getString("Enter KEY", null);

        // Основной LinearLayout для всего диалога
        LinearLayout mainLayout = new LinearLayout(context);
        mainLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        mainLayout.setOrientation(LinearLayout.VERTICAL);
        mainLayout.setBackgroundColor(Color.parseColor("#141414"));
        mainLayout.setPadding(50, 50, 50, 50);

        // Заголовок "Авторизация"
        TextView titleTextView = new TextView(context);
        titleTextView.setText(name2());
        titleTextView.setTextColor(Color.WHITE);
        titleTextView.setTextSize(26);
        titleTextView.setGravity(Gravity.CENTER);
        titleTextView.setTypeface(null, Typeface.BOLD);
        titleTextView.setPadding(0, 0, 0, 40);
        mainLayout.addView(titleTextView);

        // LinearLayout для метки и EditText
        LinearLayout inputLayout = new LinearLayout(context);
        inputLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        inputLayout.setOrientation(LinearLayout.VERTICAL);

        // EditText для ввода ключа
        final EditText keyEditText = new EditText(context);
        keyEditText.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        keyEditText.setHint(name3());
        keyEditText.setHintTextColor(Color.WHITE);
        keyEditText.setTextColor(Color.WHITE);
        keyEditText.setTextSize(20);
        keyEditText.setPadding(20, 25, 20, 25);
        keyEditText.setBackgroundColor(Color.TRANSPARENT);

        // Устанавливаем текст в EditText только если struser не null и не пустой
        if (struser != null && !struser.isEmpty()) {
            keyEditText.setText(struser);
        } else {
            keyEditText.setText(""); // Убедитесь, что EditText пустой
        }

        keyEditText.setGravity(Gravity.BOTTOM);
        inputLayout.addView(keyEditText);

        // Подчеркивание под EditText (линия)
        View underline = new View(context);
        underline.setLayoutParams(new LinearLayout.LayoutParams(-1, 3));
        underline.setBackgroundColor(Color.parseColor("#555555"));
        underline.setPadding(20,0,20,0);
        inputLayout.addView(underline);

        mainLayout.addView(inputLayout);

        // Кнопка "Войти"
        Button loginButton = new Button(context);
        loginButton.setLayoutParams(new LinearLayout.LayoutParams(-1, 120));
        loginButton.setText(name4());
        loginButton.setTextColor(Color.WHITE);
        loginButton.setTextSize(20);
        loginButton.setTypeface(null, Typeface.BOLD);
        loginButton.setGravity(Gravity.CENTER);
        loginButton.setPadding(0, 0, 0, 0);

        // GradientDrawable для кнопки
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setColor(Color.parseColor("#9C27B0"));
        gradientDrawable.setCornerRadius(10);
        loginButton.setBackground(gradientDrawable);

        mainLayout.addView(loginButton);

        // Кнопка "Получить ключ"
        Button getKeyButton = new Button(context);
        getKeyButton.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        getKeyButton.setText(name5());
        getKeyButton.setTextColor(Color.WHITE);
        getKeyButton.setTextSize(18);
        getKeyButton.setGravity(Gravity.CENTER);
        getKeyButton.setPadding(30, 30, 30, 30);
        getKeyButton.setBackgroundColor(Color.TRANSPARENT);
        mainLayout.addView(getKeyButton);

        // Создание AlertDialog
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setView(mainLayout);
        builder.setCancelable(false);

        final AlertDialog alertDialog = builder.create();
        alertDialog.show();

        // Обработчик нажатия на кнопку "Войти"
        loginButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View view) {
					String key = keyEditText.getText().toString().trim();

					if (key.equals(CORRECT_KEY)) {
						// Ключ верный
						SharedPreferences.Editor edit = sharedPreferences.edit();
						edit.putString("Enter KEY", key);
						edit.apply();

						alertDialog.dismiss();
						Toast.makeText(context, name6(), Toast.LENGTH_SHORT).show();
						Toast.makeText(context, name7(), Toast.LENGTH_SHORT).show();

						// Запускаем Main.Start с задержкой
						new Handler().postDelayed(new Runnable() {
								@Override
								public void run() {
									Main.start(context);
								}
							}, 4700); //4,7 секунд запустится файл Main.java

					} else {
						// Ключ неверный
						keyEditText.setHintTextColor(Color.RED);
						keyEditText.setHint(name8());
						keyEditText.setText("");
						Toast.makeText(context, name9(), Toast.LENGTH_SHORT).show();
					}
				}
			});

        // Обработчик нажатия на кнопку "Получить ключ"
        getKeyButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View view) {
					Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(GET_KEY_URL));
					context.startActivity(browserIntent);
				}
			});

        // Блокируем запуск Main.Start до ввода правильного ключа
        SharedPreferences.Editor editor = sharedPreferences.edit();
        boolean keyEntered = sharedPreferences.contains("Enter KEY") && sharedPreferences.getString("Enter KEY", null).equals(CORRECT_KEY);
        if (!keyEntered) {
            editor.putBoolean("keyEntered", false);
            editor.apply();
        } else {
            editor.putBoolean("keyEntered", true);
            editor.apply();
        }
    }
}

