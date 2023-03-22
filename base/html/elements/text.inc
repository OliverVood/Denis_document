<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\Template;

	abstract class Text {

		public static function ToVar(string $name, string $value = '', array $params = []): string {
			Template::Start();
			self::Render($name, $value, $params);
			return Template::Read();
		}

		public static function Render(string $name, string $value = '', array $params = []): void {
			$type = $params['type'] ?? 'text';
		?>
			<input type = "<?= $type; ?>" name = "<?= $name; ?>" value = "<?= $value; ?>">
		<?php }

	}