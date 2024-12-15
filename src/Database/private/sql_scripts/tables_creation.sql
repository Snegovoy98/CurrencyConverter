
CREATE TABLE IF NOT EXISTS settings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    setting_name TEXT NOT NULL,
    setting_value TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS exchange_history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    currency_on_exchange_title TEXT NOT NULL,
    value_per_unit double NOT NULL,
    currency_to_exchange_title TEXT NOT NULL,
    exchanged_sum double NOT NULL,
    exchange_date INTEGER NOT NULL
);
