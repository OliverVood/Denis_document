<?php

	namespace Base;

	use SQLite3;

	class VersionsControl extends SQLite3 {
		protected static ?self $instance = null;
		private array $versions = [];

		private function __construct($filename) {
			parent::__construct($filename);
		}

		public static function instance(): ?self { return self::$instance; }
		public static function init($filename): void { if (!self::$instance) self::$instance = new self($filename); }

		public function Check($namespace) {
			$result = $this->query("SELECT * FROM `{$namespace}`");
			while ($item = $result->fetchArray(SQLITE3_ASSOC)) {
				$hash = hash_file('md5', DIR_ROOT . $item['file']);
				if ($hash != $item['hash']) $this->query("UPDATE `{$namespace}` SET `hash` = '{$hash}', `micro` = `micro` + 1 WHERE `const` = '{$item['const']}'");
			}
		}

		public function Select($namespace) {
			$result = $this->query("SELECT * FROM `{$namespace}`");
			while ($item = $result->fetchArray(SQLITE3_ASSOC)) {
				$this->versions[$namespace][$item['const']] = "{$item['major']}.{$item['minor']}.{$item['micro']}";
			}
		}

		public function Get($namespace, $const): string {
			if (!isset($this->versions[$namespace])) {
				$this->Check($namespace);
				$this->Select($namespace);
			}

			return $this->versions[$namespace][$const];
		}

	}

	VersionsControl::init(DIR_FILES . 'versions.db');