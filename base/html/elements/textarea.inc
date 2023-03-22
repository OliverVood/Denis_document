<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\Template;

	abstract class Textarea {

		public static function ToVar(string $name, string $value = '', array $params = []): string {
			Template::Start();
			self::Render($name, $value, $params);
			return Template::Read();
		}

		public static function Render(string $name, string $value = '', array $params = []): void { ?>
			<label>
				<textarea name = "<?= $name; ?>"><?= $value; ?></textarea>
			</label>
		<?php }

	}