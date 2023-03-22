<?php

	namespace Base\Templates\HTML\Element;

	use Base\Templates\Template;

	abstract class Select {

		public static function ToVar(string $name, string $value = '', array $data = [], array $params = []): string {
			Template::Start();
			self::Render($name, $value, $data, $params);
			return Template::Read();
		}

		public static function Render(string $name, string $value = '', array $data = [], array $params = []): void { ?>
			<label>
				<select name = "<?= $name; ?>">
					<?php foreach ($data as $key => $text) { ?>
							<option value = "<?= $key; ?>"<?= ($key == $value) ? 'selected' : '' ?>><?= $text; ?></option>
					<?php } ?>
				</select>
			</label>
		<?php }

	}