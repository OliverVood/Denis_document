<?php

	namespace Base\Templates;

	abstract class Layout {
		private static array $stylesheets = [];
		private static array $scripts = [];

		public function __construct() {  }

		public static function AddStylesheet(string $name, string $url): void {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] = $url;
		}

		public static function AddVersionStylesheet(string $name, string $file_path_and_name, string $version): void {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] ="{$file_path_and_name}.{$version}.css";
		}

		public static function BrowseStylesheets(): void {
			foreach (self::$stylesheets as $url) { ?><link rel = "stylesheet" href = "<?= $url; ?>" type = "text/css"><?php }
		}

		public static function AddScript(string $name, string $src) : void {
			if (isset(self::$scripts[$name])) die("Script «{$name}» exists");
			self::$scripts[$name] = $src;
		}

		public static function AddVersionScript(string $name, string $file_path_and_name, string $version) : void {
			if (isset(self::$scripts[$name])) die("Script «{$name}» exists");
			self::$scripts[$name] = "{$file_path_and_name}.{$version}.js";
		}

		public static function BrowseScripts(): void {
			foreach (self::$scripts as $src) { ?><script src = "<?= $src; ?>"></script><?php }
		}

	}