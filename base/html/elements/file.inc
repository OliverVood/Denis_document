<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\Template;

	abstract class File {

		public static function ToVar(string $name, string $value = '', array $params = []): string {
			Template::Start();
			self::Render($name, $value, $params);
			return Template::Read();
		}

		public static function Render(string $name, string $value = '', array $params = []): void {
			$accept = isset($params['accept']) ? ' accept = "' . $params['accept'] . '"' : '';
		?>
			<input type = "file" name = "<?= $name; ?>" value = "<?= $value; ?>"<?= $accept; ?>>
		<?php }

	}