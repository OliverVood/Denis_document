<?php

	namespace Base\Templates\HTML\Element;

	class Form {
		private array $data;

		public function __construct(array $data = []) {
			$this->data = $data;
		}

		public function Begin(string $action = ''): void { ?>
			<form action = "<?= $action; ?>">
		<?php }

		public function End(): void { ?>
			</form>
		<?php }

		public function Submit(string $value = 'Отправить', $click = ''): void {
			if ($click) $click = ' onclick = "' . $click . '"';
		?>
			<input type = "submit" value = "<?= $value; ?>"<?= $click; ?>>
		<?php }

		public function Element(string $skin, string $name, string | int $value, array $params = []): void {
			switch ($skin) {
				case 'hidden': Text::object()->Render("form[{$name}]", $value, ['type' => 'hidden']); break;
				case 'text': Text::object()->Render("form[{$name}]", $value, $params); break;
				case 'file': File::object()->Render("form[{$name}]", $value, $params); break;
				case 'select': Select::object()->Render("form[{$name}]", $value, $this->data[$name] ?? [], $params); break;
				case 'textarea': Textarea::object()->Render("form[{$name}]", $value, $params); break;
				case 'datetime': Text::object()->Render("form[{$name}]", $value, ['type' => 'datetime-local']); break;
				default: echo 'ELEMENT NOT FOUND'; break;
			}
		}

	}