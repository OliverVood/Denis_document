<?php

	namespace Base\Templates;

	abstract class Layout {
		private static array $stylesheets = [];
		private static array $scripts = [];

		public function __construct() {  }

		public static function AddStylesheet($name, $url) {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] = $url;
		}

		public static function BrowseStylesheets() {
			foreach (self::$stylesheets as $url) { ?><link rel = "stylesheet" href = "<?= $url; ?>" type = "text/css"><?php }
		}

		public static function AddScripts($name, $src) {
			if (isset(self::$scripts[$name])) die("Script «{$name}» exists");
			self::$scripts[$name] = $src;
		}

		public static function BrowseScripts() {
			foreach (self::$scripts as $src) { ?><script src = "<?= $src; ?>"></script><?php }
		}

	}